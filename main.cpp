#include <QApplication>
#include "mainwindow.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <Utilidades/database.h>
#include <Utilidades/configuracionxml.h>
#include <procesarinformacion.h>
#include <QDateTime>
#include <Utilidades/logs.h>

// Funcion para mostrar la ayuda
void muestroAyuda();

// Variables de entorno
QString _accion="";
QString _reclamosABorrar="0";

QString _version="1.9.1";

//1.4.1 - Se corrige un error al cargar una tarea que contiene en la descripción una barrita / .
//1.5.0 - Se agrega soporte para el campo de sintomas.
//1.6.0 - Se modifica la consulta de reclamos para agregar los numeros de serie desde las tareas.
//1.6.1 - Se agrega un filtrado para el numero de serie, para quitar los espacios en blanco, los guiones y hacer mayusculas todas las letras.
//1.7.0 - Se modifica la consulta de reclamos para que, si la causa es bug aplicativo, se marque el reclamo como coordinado.
//1.7.1 - Se modifican las consulta para que cuando haya un campo con comillas, se reemplace por un espacio o sin espacios.
//1.8.0 - Se modifican las consulta para contemplar un nuevo estado(18 - Sin respuesta de Objetos)
//      - Se le asigna a los reclmos que terminaron como Sin respuesta de Objetos, la causa "No se encontro la causa"
//1.9.0 - Se agregan 2 nuevas columnas a la tabla Reclamos, para informar el tipo de reclamo
//1.9.1 - Corrección en las consultas para soportar mysql 5.7

int main(int argc, char *argv[])
{

    Logs::depurarLog();

    /// Codificacion del sistema para aceptar tildes y ñ
    QTextCodec *linuxCodec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);


    /// Si no hay argumentos arranco la aplicación en modo GUI
    if(argc==1){

        if(!ConfiguracionXml::leerConfiguracionXml()){
            muestroAyuda(); exit(0);}

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        Logs::loguear("Inicio de aplicación de carga de almacen[MODO GRAFICO], ver: "+_version);
        return a.exec();

    }else{
        QCoreApplication app(argc, argv);
        Logs::loguear("Inicio de aplicación de carga de almacen[MODO CONSOLA], ver: "+_version);

        /// Hago la evaluacion de argumentos
        for (int i=0; i< argc; i++){
            QString _argumentos(argv[i]);

            if(_argumentos.compare("--help",Qt::CaseInsensitive)==0 || _argumentos.compare("--ayuda",Qt::CaseInsensitive)==0 || _argumentos.compare("-?",Qt::CaseInsensitive)==0 || _argumentos.compare("-version",Qt::CaseInsensitive)==0 || _argumentos.compare("-v",Qt::CaseInsensitive)==0 || _argumentos.compare("--version",Qt::CaseInsensitive)==0){

                _accion="ayuda";
                break;

            }else if(_argumentos.compare("batch",Qt::CaseSensitive)==0){

                _accion="batch";

            }else if(_argumentos.compare("nuevos",Qt::CaseSensitive)==0){

                _accion="nuevos";
            }

            if(i==2){
                if(_argumentos.compare("--meses",Qt::CaseInsensitive)==0);{
                    QString _otroArgumentos(argv[3]);
                    if(_otroArgumentos.trimmed().compare("",Qt::CaseInsensitive)==0){
                        _accion="ayuda";
                        break;
                    }else{
                        _reclamosABorrar=_otroArgumentos.trimmed();
                        Logs::loguear("Cantidad de meses a borrar: "+_otroArgumentos.trimmed());

                    }
                }
            }
        }

        if(_accion=="ayuda"){
            Logs::loguear("Muestra la ayuda y se cierra la aplicación");
            muestroAyuda();
            exit(0);
        }else if(_accion=="batch"){
            if(!ConfiguracionXml::leerConfiguracionXml()){
                Logs::loguear("Muestra la ayuda y se cierra la aplicación");
                muestroAyuda();
                exit(0);
            }

            ProcesarInformacion::retornaReclamoDondeEmpezarABorrar("MODO CONSOLA",_reclamosABorrar.toInt());
            /// Cargo las consultas Sql
            ProcesarInformacion::setearConsultasSql();

            QString HoraComienzo =QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
            Logs::loguear("\tFecha hora comienzo: "+HoraComienzo);


            Logs::loguear("Asignando causa a reclamos en madai Sin respuesta De Objeto(18):");
            ProcesarInformacion::reclamosAlosCualesHayQueAsignarCausaYSintoma();



            Logs::loguear("1 - Borrar tablas temporales si existen: ");
            if(ProcesarInformacion::borrarTablasDBOrigen()){
                Logs::loguear("\tTablas temporales borradas OK.");
                Logs::loguear("2 - Crear tablas temporales: ");
                if(ProcesarInformacion::crearTablasTemporales()){
                    Logs::loguear("\tTablas temporales creadas OK.");
                    Logs::loguear("3 - Eliminar datos tablas temporales: ");
                    if(ProcesarInformacion::eliminarDatosTemporalesDBOrigen()){
                        Logs::loguear("\tDatos temporales borrados OK.");
                        Logs::loguear("4 - Cargar tiempo de reclamos: ");
                        if(ProcesarInformacion::cargoDatosReclamosTiempos()){
                            Logs::loguear("\tTiempos cargados OK.");
                            Logs::loguear("5 - Eliminar datos base Almacen: ");
                            if(ProcesarInformacion::eliminarDatosDBDestino()){
                                Logs::loguear("\tDatos eliminados OK.");
                                Logs::loguear("6 - Leer información de reclamos en Madai: ");
                                if(ProcesarInformacion::leerDatosDBOrigenReclamos()){
                                    Logs::loguear("\tDatos leidos OK.");
                                    Logs::loguear("7 - Leer información de tareas en Madai: ");
                                    if(ProcesarInformacion::leerDatosDBOrigenTareas()){
                                        Logs::loguear("\tDatos leidos OK.");
                                        Logs::loguear("8 - Leer información de conceptos en Madai: ");
                                        if(ProcesarInformacion::leerDatosDBOrigenConceptos()){
                                            Logs::loguear("\tDatos leidos OK.");
                                            Logs::loguear("9 - Preparar reclamos para calculo de tiempo estimados: ");
                                            if(ProcesarInformacion::prepararReclamosParaCalcularTiempos()){
                                                Logs::loguear("\tReclamos preparados OK.");
                                                Logs::loguear("10 - Borrar tablas temporales: ");
                                                if(ProcesarInformacion::borrarTablasDBOrigen()){
                                                    Logs::loguear("\tTablas temporales borradas OK.");

                                                    Logs::loguear("11 - Informar reclamos que no pudieron ser cargados:");
                                                    ProcesarInformacion::recavarReclamosQueNoSeCargan();

                                                    Logs::loguear("\tFin de la carga de reclamos.");
                                                    Logs::loguear("\tFecha hora fin: "+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
                                                    Logs::loguear("\tTiempo total de carga: MINUTOS = " +QString::number(QDateTime::fromString(HoraComienzo,"yyyy-MM-dd HH:mm").secsTo(QDateTime::currentDateTime())/60));

                                                }else{
                                                    Logs::loguear("Error al borrar las tablas temporales de MADAI");
                                                    ProcesarInformacion::informeDeCargaDeDatosAlmacen("Error al borrar las tablas temporales de MADAI");
                                                }
                                            }else{
                                                Logs::loguear("Error al preparar reclamos para calculo de tiempo");
                                                ProcesarInformacion::informeDeCargaDeDatosAlmacen("Error al preparar reclamos para calculo de tiempo");
                                            }
                                        }else{
                                            Logs::loguear("Error al cargar Conceptos");
                                            ProcesarInformacion::informeDeCargaDeDatosAlmacen("Error al cargar Conceptos");
                                        }
                                    }else{
                                        Logs::loguear("Error al cargar Tareas");
                                        ProcesarInformacion::informeDeCargaDeDatosAlmacen("Error al cargar Tareas");
                                    }
                                }else{
                                    Logs::loguear("Error al cargar Reclamos");
                                    ProcesarInformacion::informeDeCargaDeDatosAlmacen("Error al cargar Reclamos");
                                }
                            }else{
                                Logs::loguear("No se puede acceder a la base de datos destino");
                                ProcesarInformacion::informeDeCargaDeDatosAlmacen("No se puede acceder a la base de datos destino");
                            }
                        }else{
                            Logs::loguear("No se pudieron cargar los datos temporales para obtener el tiempo en estado nuevo de un reclamo");
                            ProcesarInformacion::informeDeCargaDeDatosAlmacen("No se pudieron cargar los datos temporales para obtener el tiempo en estado nuevo de un reclamo");
                        }
                    }else{
                        Logs::loguear("No se pudieron borrar los datos temporales");
                        ProcesarInformacion::informeDeCargaDeDatosAlmacen("No se pudieron borrar los datos temporales");
                    }
                }else{
                    Logs::loguear("No se pudieron crear las tablas temporales");
                    ProcesarInformacion::informeDeCargaDeDatosAlmacen("No se pudieron crear las tablas temporales");
                }
            }else{
                Logs::loguear("No se pudieron dropear las tablas temporales");
                ProcesarInformacion::informeDeCargaDeDatosAlmacen("No se pudieron dropear las tablas temporales");
            }




        }else if(_accion=="nuevos"){




        }else if(_accion==""){
            muestroAyuda();
            Logs::loguear("Muestra la ayuda y se cierra la aplicación");
            exit(0);
        }
    }
}

/// Funcion que muestra el ayuda de la aplicación
void muestroAyuda(){


    qDebug()<< "###############################";
    qDebug()<< "\tVersión "+_version+"\n###############################";
    qDebug()<< "\nFORMAS DE USO:";
    qDebug()<< "\n* Para ejecutar la aplicación en modo grafico, no le pase parametros.\n  Ejemplo: ./CargaAlmacenDeDatos";
    qDebug()<< "\n* Para ejecutar la aplicación en consola, pase como parametro 'batch'.\n  Ejemplo: ./CargaAlmacenDeDatos batch";
    qDebug()<< "\n* Si desea cargar solo algunos meses hacia atras, indique la cantidad de meses.\n  Ejemplo: ./CargaAlmacenDeDatos batch --meses 2";
    qDebug()<< "\n* Para visualizar esta ayuda, pase como parametro [--ayuda, --help, -?, -version, --version, -v].\n  Ejemplo: ./CargaAlmacenDeDatos --ayuda";
    qDebug()<< "";

}
