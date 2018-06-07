#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <procesarinformacion.h>
#include <QMessageBox>
#include <QDateTime>
#include <Utilidades/logs.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCargar_clicked()
{

    ProcesarInformacion::retornaReclamoDondeEmpezarABorrar("MODO GRAFICO",ui->sbMesesADepurar->value());

    /// Cargo las consultas Sql
    ProcesarInformacion::setearConsultasSql();



    QMessageBox mensaje;
    mensaje.setWindowTitle("Información de estado:");
    QString HoraComienzo =QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");

    Logs::loguear("\nFecha hora comienzo: "+HoraComienzo);
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
                                            Logs::loguear("\nFin de la carga de reclamos.");

                                            Logs::loguear("11 - Informar reclamos que no pudieron ser cargados:");
                                            ProcesarInformacion::recavarReclamosQueNoSeCargan();

                                            Logs::loguear("\nFecha hora fin: "+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
                                            mensaje.setText("Carga de datos completa.\n\nFecha/Hora comienzo: \t"+HoraComienzo +"\nFecha/Hora fin: \t"+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm")+"\nTiempo total de carga: MINUTOS = " +QString::number(QDateTime::fromString(HoraComienzo,"yyyy-MM-dd HH:mm").secsTo(QDateTime::currentDateTime())/60));
                                            mensaje.exec();

                                        }else{
                                            Logs::loguear("Error al borrar las tablas temporales de MADAI");
                                            mensaje.setText("Error al borrar las tablas temporales de MADAI");
                                            mensaje.exec();
                                        }
                                    }else{
                                        Logs::loguear("Error al preparar reclamos para calculo de tiempo");
                                        mensaje.setText("Error al cargar Conceptos");
                                        mensaje.exec();
                                    }
                                }else{
                                    Logs::loguear("Error al cargar Conceptos");
                                    mensaje.setText("Error al cargar Conceptos");
                                    mensaje.exec();
                                }
                            }else{
                                Logs::loguear("Error al cargar Tareas");
                                mensaje.setText("Error al cargar Tareas");
                                mensaje.exec();
                            }
                        }else{
                            Logs::loguear("Error al cargar Reclamos");
                            mensaje.setText("Error al cargar Reclamos");
                            mensaje.exec();
                        }
                    }else{
                        Logs::loguear("No se puede acceder a la base de datos destino");
                        mensaje.setText("No se puede acceder a la base de datos destino");
                        mensaje.exec();
                    }
                }else{
                    Logs::loguear("No se pudieron cargar los datos temporales para obtener el tiempo en estado nuevo de un reclamo");
                    mensaje.setText("No se pudieron cargar los datos temporales para obtener el tiempo en estado nuevo de un reclamo");
                    mensaje.exec();
                }
            }else{
                Logs::loguear("No se pudieron borrar los datos temporales");
                mensaje.setText("No se pudieron borrar los datos temporales");
                mensaje.exec();
            }
        }else{
            Logs::loguear("No se pudieron crear las tablas temporales");
            mensaje.setText("No se pudieron crear las tablas temporales");
            mensaje.exec();
        }
    }else{
        Logs::loguear("No se pudieron dropear las tablas temporales");
        mensaje.setText("No se pudieron dropear las tablas temporales");
        mensaje.exec();
    }
}

void MainWindow::on_sbMesesADepurar_editingFinished()
{


}

void MainWindow::on_sbMesesADepurar_valueChanged(int arg1)
{
}
