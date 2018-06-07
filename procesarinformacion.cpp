#include "procesarinformacion.h"
#include <Utilidades/database.h>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <Utilidades/logs.h>
#include <QDebug>
#include "QProcess"

QString ProcesarInformacion::consultaSqlRemotaReclamos;
QString ProcesarInformacion::consultaSqlRemotaTareas;
QString ProcesarInformacion::consultaSqlRemotaConceptos;
QString ProcesarInformacion::reclamoDesdeDondeEmpezarABorrar;
QString _consultaReclamos;
QString _consultaTareas;
QString _consultaConceptos;

ProcesarInformacion::ProcesarInformacion()
{
}
bool ProcesarInformacion::leerDatosDBOrigenReclamos(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        QString _insertsReclamos="";
        // Ejecuto consulta a base remota para obtener reclamos
        if(query.exec(ProcesarInformacion::getConsultaSqlRemotaReclamos())){
            QSqlRecord rec = query.record();

            while(query.next())
            {
                _insertsReclamos="SET SQL_MODE='';INSERT INTO Reclamos (codigoReclamo,codigoTipoReclamo,nombreTipoReclamo,fechaCompletaReclamo,horaCompletaReclamo,codigoArea,nombreArea,codigoTecnicoResponsable,nombreTecnicoResponsable,codigoEstado,nombreEstado,codigoAnio,codigoMes,nombreMes,numeroDiaDelMes,codigoDiaSemana,nombreDiaSemana,numeroHora,numeroMinuto,codigoCliente,razonCliente,nombreCliente,codigoSucursal,razonSucursal,nombreSucursal,codigoModelo,nombreModelo,codigoMarca,nombreMarca,numeroSerie,codigoCausa,nombreCausa,causaAtribuida,cantidadTareas,tiempoMesaEntrada,tiempoEstadoNuevo,tiempoEstadoAsignado,tiempoEsperaRespuestaCliente,tiempoEsperaRespuestaObjetos,tiempoTareas,tiempoResolucion,tituloReclamo,codigoTipo,nombreTipo,tiempoEsperaRespuestaClienteHorarioSisteco,codigoDepartamento,nombreDepartamento,codigoCoordinado,nombreCoordinado,direccionSucursal,nombreSolicitante,nombreFirmoCierre,horaCompletaFinalizacion,fechaCompletaFinalizacion,causaDeCliente,codigoCamino,nombreCamino,codigoSintoma,nombreSintoma,codigoTipoReclamoCliente,nombreTipoReclamoCliente) "
                                 "values("+query.value(rec.indexOf("CodigoReclamo")).toString()+","+query.value(rec.indexOf("CodigoTipoReclamo")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreTipoReclamo")).toString()+"','"+query.value(rec.indexOf("FechaCompleta")).toString()+"',"
                                 "'"+query.value(rec.indexOf("HoraCompleta")).toString()+"',"+query.value(rec.indexOf("CodigoArea")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreArea")).toString()+"',"+query.value(rec.indexOf("CodigoTecnico")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreTecnico")).toString()+"',"+query.value(rec.indexOf("CodigoEstado")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreEstado")).toString()+"',"+query.value(rec.indexOf("CodigoAño")).toString()+","
                                 " "+query.value(rec.indexOf("CodigoMes")).toString()+",'"+query.value(rec.indexOf("NombreMes")).toString()+"',"
                                 " "+query.value(rec.indexOf("NumeroDia")).toString()+","+query.value(rec.indexOf("CodigoDiaEnSemana")).toString()+","
                                 "'"+query.value(rec.indexOf("DiaSemana")).toString()+"',"+query.value(rec.indexOf("NumeroHora")).toString()+","
                                 " "+query.value(rec.indexOf("NumeroMinuto")).toString()+","+query.value(rec.indexOf("CodigoCliente")).toString()+","
                                 "'"+query.value(rec.indexOf("RazonCliente")).toString()+"','"+query.value(rec.indexOf("NombreCliente")).toString()+"',"
                                 " "+query.value(rec.indexOf("CodigoSucursal")).toString()+",'"+query.value(rec.indexOf("RazonSucursal")).toString()+"',"
                                 "'"+query.value(rec.indexOf("NombreSucursal")).toString()+"',"+query.value(rec.indexOf("CodigoModelo")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreModelo")).toString()+"',"+query.value(rec.indexOf("CodigoMarca")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreMarca")).toString()+"','"+query.value(rec.indexOf("NumeroSerie")).toString()+"',"
                                 " "+query.value(rec.indexOf("CodigoCausa")).toString()+",'"+query.value(rec.indexOf("NombreCausa")).toString()+"',"
                                 "'"+query.value(rec.indexOf("CausaAtribuible")).toString()+"',"+query.value(rec.indexOf("CantidadTareas")).toString()+","
                                 "'0',"
                                 "'0','0','0','0','0','0',"
                                 "'"+query.value(rec.indexOf("TituloReclamo")).toString()+"',"
                                 " "+query.value(rec.indexOf("CodigoTipo")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreTipo")).toString()+"',"
                                 "'0',"
                                 " "+query.value(rec.indexOf("CodigoDepartamento")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreDepartamento")).toString()+"',"
                                 " "+query.value(rec.indexOf("CodigoCoordinado")).toString()+","
                                 "'"+query.value(rec.indexOf("NombreCoordinado")).toString()+"',"


                                 "'"+query.value(rec.indexOf("DireccionSucursal")).toString()+"',"
                                 "'"+query.value(rec.indexOf("NombreSolicitante")).toString()+"',"
                                 "'"+query.value(rec.indexOf("NombreFirmoCierre")).toString()+"',";

                if(query.value(rec.indexOf("HoraFinalizacion")).toString().trimmed()==""){
                    _insertsReclamos+="'00:00:00',";
                }else{
                    _insertsReclamos+="'"+query.value(rec.indexOf("HoraFinalizacion")).toString() +"',";

                }
                if(query.value(rec.indexOf("FechaFinalizacion")).toString().trimmed()==""){
                    _insertsReclamos+="'0000-00-00',";
                }else{
                    _insertsReclamos+="'"+query.value(rec.indexOf("FechaFinalizacion")).toString()+"',";

                }
                _insertsReclamos+="'"+query.value(rec.indexOf("CausaDeCliente")).toString()+"',";
                _insertsReclamos+=" "+query.value(rec.indexOf("CodigoCamino")).toString()+",";
                _insertsReclamos+="'"+query.value(rec.indexOf("NombreCamino")).toString()+"',";
                _insertsReclamos+=" "+query.value(rec.indexOf("CodigoSintoma")).toString()+",";
                _insertsReclamos+="'"+query.value(rec.indexOf("NombreSintoma")).toString()+"',";

                _insertsReclamos+=" "+query.value(rec.indexOf("CodigoTipoReclamoCliente")).toString()+",";
                _insertsReclamos+="'"+query.value(rec.indexOf("NombreTipoReclamoCliente")).toString()+"'";

                //codigoTipoReclamoCliente
                //nombreTipoReclamoCliente

                _insertsReclamos+=")";



                if(!ProcesarInformacion::grabarDatosDBDestino(_insertsReclamos)){
                    Logs::loguear("Error al insertar reclamo número "+query.value(rec.indexOf("CodigoReclamo")).toString());
                    Logs::loguear("Insert: "+_insertsReclamos);
                    Logs::loguear(query.lastError().text());
                    return false;
                }
            }
            return true;
        }else{  return false; }
    }else{ return false; }
}

bool ProcesarInformacion::leerDatosDBOrigenTareas(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        QString _insertsTareas="";
        // Ejecuto consulta a base remota para obtener tareas
        if(query.exec(ProcesarInformacion::getConsultaSqlRemotaTareas())){
            QSqlRecord rec = query.record();
            while(query.next())
            {
                _insertsTareas="SET SQL_MODE='';INSERT INTO Tareas (idReclamo,codigoTarea,nombreTarea,fechaTarea,horaTarea,comentarioTarea,tiempoTarea,nombreTareaReporte) "
                               "values("+query.value(rec.indexOf("CodigoReclamo")).toString()+","+query.value(rec.indexOf("CodigoTarea")).toString()+","
                               "'"+query.value(rec.indexOf("NombreTarea")).toString()+"','"+query.value(rec.indexOf("FechaTarea")).toString()+"',";

                if(query.value(rec.indexOf("HoraTarea")).toString().trimmed()==""){
                    _insertsTareas+="'00:00:00',";
                }else{
                    _insertsTareas+="'"+query.value(rec.indexOf("HoraTarea")).toString()+"',";
                }
                _insertsTareas+="'"+query.value(rec.indexOf("ComentariosTareas")).toString().replace("\\","\\\\",Qt::CaseSensitive)+"',"
                                "'"+query.value(rec.indexOf("TiempoTarea")).toString()+"',"
                                "'"+query.value(rec.indexOf("NombreTareaReporte")).toString()+"'"
                                ")";



                if(!ProcesarInformacion::grabarDatosDBDestino(_insertsTareas)){
                    Logs::loguear("Error al insertar tarea  "+query.value(rec.indexOf("CodigoTarea")).toString()+ " Reclamo: "+query.value(rec.indexOf("CodigoReclamo")).toString());
                    Logs::loguear(query.lastError().text());
                    return false;
                }
            }
            return true;
        }else{
            Logs::loguear("Error: Función leerDatosDBOrigenTareas::getConsultaSqlRemotaTareas()");
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        Logs::loguear("Conexion offline");
        return false;
    }
}

bool ProcesarInformacion::leerDatosDBOrigenConceptos(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        QString _insertsConceptos="";
        // Ejecuto consulta a base remota para obtener tareas
        if(query.exec(ProcesarInformacion::getConsultaSqlRemotaConceptos())){
            QSqlRecord rec = query.record();
            while(query.next())
            {
                _insertsConceptos="SET SQL_MODE='';INSERT INTO Conceptos (idReclamo,codigoConcepto,nombreConcepto) "
                                  "values("+query.value(rec.indexOf("CodigoReclamo")).toString()+","+query.value(rec.indexOf("CodigoConcepto")).toString()+","
                                  "'"+query.value(rec.indexOf("NombreConcepto")).toString()+"'"
                                  ")";

                //Logs::loguear("Insert de conceptos "+_insertsConceptos);

                if(!ProcesarInformacion::grabarDatosDBDestino(_insertsConceptos)){
                    Logs::loguear("Error al insertar concepto  "+query.value(rec.indexOf("CodigoConcepto")).toString()+ " Reclamo: "+query.value(rec.indexOf("CodigoReclamo")).toString());
                    return false;
                }
            }
            return true;
        }else{
            Logs::loguear("Error: Función leerDatosDBOrigenConceptos::getConsultaSqlRemotaConceptos()");
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        Logs::loguear("Conexion offline");
        return false;
    }
}




bool ProcesarInformacion::grabarDatosDBDestino(QString _insertBaseDeDatos){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos de almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec(_insertBaseDeDatos)){
            return true;
        }else{
            Logs::loguear("Error: Función grabarDatosDBDestino == Insert base de datos: "+_insertBaseDeDatos);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{}
}

bool ProcesarInformacion::eliminarDatosDBDestino(){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos de almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("delete from Tareas where idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'")){
            if(query.exec("delete from Reclamos where codigoReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'")){
                if(query.exec("delete from Conceptos where idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'")){
                    return true;
                }else{
                    Logs::loguear("Función eliminarDatosDBDestino::Delete from Conceptos");
                    Logs::loguear(query.lastError().text());
                    return false;
                }
            }else{
                Logs::loguear("Función eliminarDatosDBDestino::Delete from Reclamos");
                Logs::loguear(query.lastError().text());
                return false;
            }
        }else{
            Logs::loguear("Función eliminarDatosDBDestino::Delete from Tareas");
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}

bool ProcesarInformacion::eliminarDatosTemporalesDBOrigen(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        if(query.exec("delete from tabla_EstadoNuevo1")){
            if(query.exec("delete from tabla_EstadoNuevo2")){
                if(query.exec("delete from tabla_EstadoNuevo")){
                    if(query.exec("delete from tabla_EstadoAsignado1")){
                        if(query.exec("delete from tabla_EstadoAsignado2")){
                            if(query.exec("delete from tabla_EstadoAsignado")){
                                if(query.exec("delete from tabla_EsperaCliente1")){
                                    if(query.exec("delete from tabla_EsperaCliente2")){
                                        if(query.exec("delete from tabla_EsperaCliente")){
                                            if(query.exec("delete from tabla_EsperaObjetos1")){
                                                if(query.exec("delete from tabla_EsperaObjetos2")){
                                                    if(query.exec("delete from tabla_EsperaObjetos")){
                                                        if(query.exec("delete from tabla_EstadoTotal1")){
                                                            if(query.exec("delete from tabla_EstadoTotal2")){
                                                                if(query.exec("delete from tabla_EstadoTotal")){
                                                                    return true;
                                                                }else{
                                                                    Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoTotal" );
                                                                    Logs::loguear(query.lastError().text());
                                                                    return false;}
                                                            }else{
                                                                Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoTotal2" );
                                                                Logs::loguear(query.lastError().text());
                                                                return false;}
                                                        }else{
                                                            Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoTotal1" );
                                                            Logs::loguear(query.lastError().text());
                                                            return false;}

                                                    }else{
                                                        Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaObjetos" );
                                                        Logs::loguear(query.lastError().text());
                                                        return false;}
                                                }else{
                                                    Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaObjetos2" );
                                                    Logs::loguear(query.lastError().text());
                                                    return false;}
                                            }else{
                                                Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaObjetos1" );
                                                Logs::loguear(query.lastError().text());
                                                return false;}
                                        }else{
                                            Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaCliente" );
                                            Logs::loguear(query.lastError().text());
                                            return false;}
                                    }else{
                                        Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaCliente2" );
                                        Logs::loguear(query.lastError().text());
                                        return false;}
                                }else{
                                    Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EsperaCliente1" );
                                    Logs::loguear(query.lastError().text());
                                    return false;}
                            }else{
                                Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoAsignado" );
                                Logs::loguear(query.lastError().text());
                                return false;}
                        }else{
                            Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoAsignado2" );
                            Logs::loguear(query.lastError().text());
                            return false;}
                    }else{
                        Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoAsignado1" );
                        Logs::loguear(query.lastError().text());
                        return false;}
                }else{
                    Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoNuevo" );
                    Logs::loguear(query.lastError().text());
                    return false;}
            }else{
                Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoNuevo2" );
                Logs::loguear(query.lastError().text());
                return false;}
        }else{
            Logs::loguear("Función eliminarDatosTemporalesDBOrigen::Delete from  tabla_EstadoNuevo1" );
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}

bool ProcesarInformacion::borrarTablasDBOrigen(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        if(query.exec("DROP TABLE IF EXISTS tabla_EstadoNuevo1")){
            if(query.exec("DROP TABLE IF EXISTS tabla_EstadoNuevo2")){
                if(query.exec("DROP TABLE IF EXISTS tabla_EstadoNuevo")){
                    if(query.exec("DROP TABLE IF EXISTS tabla_EstadoAsignado1")){
                        if(query.exec("DROP TABLE IF EXISTS tabla_EstadoAsignado2")){
                            if(query.exec("DROP TABLE IF EXISTS tabla_EstadoAsignado")){
                                if(query.exec("DROP TABLE IF EXISTS tabla_EsperaCliente1")){
                                    if(query.exec("DROP TABLE IF EXISTS tabla_EsperaCliente2")){
                                        if(query.exec("DROP TABLE IF EXISTS tabla_EsperaCliente")){
                                            if(query.exec("DROP TABLE IF EXISTS tabla_EsperaObjetos1")){
                                                if(query.exec("DROP TABLE IF EXISTS tabla_EsperaObjetos2")){
                                                    if(query.exec("DROP TABLE IF EXISTS tabla_EsperaObjetos")){


                                                        if(query.exec("DROP TABLE IF EXISTS tabla_EstadoTotal1")){
                                                            if(query.exec("DROP TABLE IF EXISTS tabla_EstadoTotal2")){
                                                                if(query.exec("DROP TABLE IF EXISTS tabla_EstadoTotal")){
                                                                    return true;
                                                                }else{
                                                                    Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoTotal" );
                                                                    Logs::loguear(query.lastError().text());
                                                                    return false;}
                                                            }else{
                                                                Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoTotal2" );
                                                                Logs::loguear(query.lastError().text());
                                                                return false;}
                                                        }else{
                                                            Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoTotal1" );
                                                            Logs::loguear(query.lastError().text());
                                                            return false;}


                                                    }else{
                                                        Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaObjetos" );
                                                        Logs::loguear(query.lastError().text());
                                                        return false;}
                                                }else{
                                                    Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaObjetos2" );
                                                    Logs::loguear(query.lastError().text());
                                                    return false;}
                                            }else{
                                                Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaObjetos1" );
                                                Logs::loguear(query.lastError().text());
                                                return false;}
                                        }else{
                                            Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaCliente" );
                                            Logs::loguear(query.lastError().text());
                                            return false;}
                                    }else{
                                        Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaCliente2" );
                                        Logs::loguear(query.lastError().text());
                                        return false;}
                                }else{
                                    Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EsperaCliente1" );
                                    Logs::loguear(query.lastError().text());
                                    return false;}
                            }else{
                                Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoAsignado" );
                                Logs::loguear(query.lastError().text());
                                return false;}
                        }else{
                            Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoAsignado2" );
                            Logs::loguear(query.lastError().text());
                            return false;}
                    }else{
                        Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoAsignado1" );
                        Logs::loguear(query.lastError().text());
                        return false;}
                }else{
                    Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoNuevo" );
                    Logs::loguear(query.lastError().text());
                    return false;}
            }else{
                Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoNuevo2" );
                Logs::loguear(query.lastError().text());
                return false;}
        }else{
            Logs::loguear("Función borrarTablasDBOrigen::DROP TABLE IF EXISTS tabla_EstadoNuevo1" );
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}

bool ProcesarInformacion::crearTablasTemporales(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoNuevo1 (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45), horaCambioEstado varchar(45),estado char(1),correlativo BIGINT(10))")){
            if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoNuevo2 ( id BIGINT NOT NULL AUTO_INCREMENT , codigoReclamo BIGINT(10) NOT NULL,  horaGuardado varchar(45),  horaCambioEstado varchar(45), estado char(1),correlativo BIGINT(10), PRIMARY KEY (`id`))")){
                if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoNuevo(codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45),horaCambioEstado varchar(45))")){
                    if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoAsignado1 (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45), horaCambioEstado varchar(45),estado char(1),correlativo BIGINT(10))")){
                        if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoAsignado2 ( id BIGINT NOT NULL AUTO_INCREMENT , codigoReclamo BIGINT(10) NOT NULL,  horaGuardado varchar(45),  horaCambioEstado varchar(45), estado char(1),correlativo BIGINT(10), PRIMARY KEY (`id`))")){
                            if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoAsignado(codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45),horaCambioEstado varchar(45))")){
                                if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaCliente1 (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45), horaCambioEstado varchar(45),estado char(1),correlativo BIGINT(10))")){
                                    if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaCliente2 ( id BIGINT NOT NULL AUTO_INCREMENT , codigoReclamo BIGINT(10) NOT NULL,  horaGuardado varchar(45),  horaCambioEstado varchar(45), estado char(1),correlativo BIGINT(10), PRIMARY KEY (`id`))")){
                                        if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaCliente(codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45),horaCambioEstado varchar(45))")){
                                            if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaObjetos1 (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45), horaCambioEstado varchar(45),estado char(1),correlativo BIGINT(10))")){
                                                if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaObjetos2 ( id BIGINT NOT NULL AUTO_INCREMENT , codigoReclamo BIGINT(10) NOT NULL,  horaGuardado varchar(45),  horaCambioEstado varchar(45), estado char(1),correlativo BIGINT(10), PRIMARY KEY (`id`))")){
                                                    if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EsperaObjetos (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45),horaCambioEstado varchar(45))")){
                                                        if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoTotal1 (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45), horaCambioEstado varchar(45),estado char(1),correlativo BIGINT(10))")){
                                                            if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoTotal2 ( id BIGINT NOT NULL AUTO_INCREMENT , codigoReclamo BIGINT(10) NOT NULL,  horaGuardado varchar(45),  horaCambioEstado varchar(45), estado char(1),correlativo BIGINT(10), PRIMARY KEY (`id`))")){
                                                                if(query.exec("CREATE  TABLE IF NOT EXISTS tabla_EstadoTotal (codigoReclamo BIGINT(10) NOT NULL,horaGuardado varchar(45),horaCambioEstado varchar(45))")){
                                                                    return true;
                                                                }else{
                                                                    Logs::loguear("Función crearTablasTemporales::tabla_EstadoTotal" );
                                                                    Logs::loguear(query.lastError().text());
                                                                    return false;}
                                                            }else{
                                                                Logs::loguear("Función crearTablasTemporales::tabla_EstadoTotal2" );
                                                                Logs::loguear(query.lastError().text());
                                                                return false;}
                                                        }else{
                                                            Logs::loguear("Función crearTablasTemporales::tabla_EstadoTotal1" );
                                                            Logs::loguear(query.lastError().text());
                                                            return false;}
                                                    }else{
                                                        Logs::loguear("Función crearTablasTemporales::tabla_EsperaObjetos" );
                                                        Logs::loguear(query.lastError().text());
                                                        return false;}
                                                }else{
                                                    Logs::loguear("Función crearTablasTemporales::tabla_EsperaObjetos2" );
                                                    Logs::loguear(query.lastError().text());
                                                    return false;}
                                            }else{
                                                Logs::loguear("Función crearTablasTemporales::tabla_EsperaObjetos1" );
                                                Logs::loguear(query.lastError().text());
                                                return false;}
                                        }else{
                                            Logs::loguear("Función crearTablasTemporales::tabla_EsperaCliente" );
                                            Logs::loguear(query.lastError().text());
                                            return false;}
                                    }else{
                                        Logs::loguear("Función crearTablasTemporales::tabla_EsperaCliente2" );
                                        Logs::loguear(query.lastError().text());
                                        return false;}
                                }else{
                                    Logs::loguear("Función crearTablasTemporales::tabla_EsperaCliente1" );
                                    Logs::loguear(query.lastError().text());
                                    return false;}
                            }else{
                                Logs::loguear("Función crearTablasTemporales::tabla_EstadoAsignado" );
                                Logs::loguear(query.lastError().text());
                                return false;}
                        }else{
                            Logs::loguear("Función crearTablasTemporales::tabla_EstadoAsignado2" );
                            Logs::loguear(query.lastError().text());
                            return false;}
                    }else{
                        Logs::loguear("Función crearTablasTemporales::tabla_EstadoAsignado1" );
                        Logs::loguear(query.lastError().text());
                        return false;}
                }else{
                    Logs::loguear("Función crearTablasTemporales::tabla_EstadoNuevo" );
                    Logs::loguear(query.lastError().text());
                    return false;}
            }else{
                Logs::loguear("Función crearTablasTemporales::tabla_EstadoNuevo2" );
                Logs::loguear(query.lastError().text());
                return false;}
        }else{
            Logs::loguear("Función crearTablasTemporales::tabla_EstadoNuevo1" );
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}

void ProcesarInformacion::setearConsultasSql(){
    /// Consulta para obtener los reclamos
    _consultaReclamos="select "
                      "REC.idReclamo'CodigoReclamo', "
                      "case when guardia='s' then '2'       else '1'     end 'CodigoTipoReclamo', "
                      "case when guardia='s' then 'Guardia' else 'Comun' end 'NombreTipoReclamo', "
                      "REC.fecha'FechaCompleta', "
                      "case when REC.hora is null then '0' when trim(REC.hora)='' then '0' else REC.hora end'HoraCompleta', "
                      "REC.idArea'CodigoArea', "
                      "AREA.denominacion'NombreArea', "
                      "REC.idResponsable'CodigoTecnico', "
                      "REPLACE(FUNC.nombre,'\\'','')'NombreTecnico', "
                      "REC.idEstado'CodigoEstado', "
                      "ESTA.denominacion'NombreEstado', "
                      "case when YEAR(REC.fecha) is null then 'null' else YEAR(REC.fecha) end'CodigoAño', "
                      "case when MONTH(REC.fecha) is null then 'null' else MONTH(REC.fecha) end'CodigoMes', "
                      "CASE WHEN MONTH(REC.fecha) = 1 THEN 'Enero' WHEN MONTH(REC.fecha) = 2 THEN 'Febrero' WHEN MONTH(REC.fecha) = 3 THEN 'Marzo' "
                      "WHEN MONTH(REC.fecha) = 4 THEN 'Abril' WHEN MONTH(REC.fecha) = 5 THEN 'Mayo' WHEN MONTH(REC.fecha) = 6 THEN 'Junio' "
                      "WHEN MONTH(REC.fecha) = 7 THEN 'Julio' WHEN MONTH(REC.fecha) = 8 THEN 'Agosto' WHEN MONTH(REC.fecha) = 9 THEN 'Setiembre' "
                      "WHEN MONTH(REC.fecha) = 10 THEN 'Octubre' WHEN MONTH(REC.fecha) = 11 THEN 'Noviembre' WHEN MONTH(REC.fecha) = 12 THEN 'Diciembre' "
                      "else '0' end'NombreMes', "
                      "case when DAYOFMONTH(REC.fecha) is null then '0' else DAYOFMONTH(REC.fecha) end'NumeroDia', "
                      "case when DAYOFWEEK(REC.fecha) is null then '0' else DAYOFWEEK(REC.fecha) end'CodigoDiaEnSemana', "
                      "CASE WHEN DAYOFWEEK(REC.fecha) = 1 THEN 'Domingo' WHEN DAYOFWEEK(REC.fecha) = 2 THEN 'Lunes' "
                      "WHEN DAYOFWEEK(REC.fecha) = 3 THEN 'Martes' WHEN DAYOFWEEK(REC.fecha) = 4 THEN 'Miercoles' "
                      "WHEN DAYOFWEEK(REC.fecha) = 5 THEN 'Jueves' WHEN DAYOFWEEK(REC.fecha) = 6 THEN 'Viernes' "
                      "WHEN DAYOFWEEK(REC.fecha) = 7 THEN 'Sabado' else '0' end'DiaSemana', "
                      "case when HOUR(REC.hora) is null then '0' else HOUR(REC.hora) end'NumeroHora', "
                      "case when MINUTE(REC.hora) is null then '0' else MINUTE(REC.hora) end'NumeroMinuto', "
                      "REC.idCliente'CodigoCliente',  "
                      "REPLACE(CLI.razonSocial,'\\'','')'RazonCliente', "
                      "REPLACE(CLI.nombre,'\\'','')'NombreCliente', "
                      "REC.idSucursal'CodigoSucursal', "
                      "REPLACE(SUC.razonSocial,'\\'','')'RazonSucursal', "
                      "REPLACE(SUC.nombreSucursal,'\\'','')'NombreSucursal', "
                      "REC.idProducto'CodigoModelo', "
                      "REPLACE(PROD.denominacion,'\\'','')'NombreModelo', "
                      "PROD.idMarca'CodigoMarca', "
                      "REPLACE(MARC.denominacion,'\\'','')'NombreMarca', "
                      "case when REC.numeroSerie is null or REC.numeroSerie='' then "
                      "case when (select RTA.valorAtributo from reclamoTareasAtributos RTA where RTA.idReclamo=REC.idReclamo and RTA.idAtributo=17 limit 1) is null or (select RTA.valorAtributo from reclamoTareasAtributos RTA where RTA.idReclamo=REC.idReclamo and RTA.idAtributo=17 limit 1)='' "
                      "then UPPER(REPLACE(REPLACE(REC.numeroSerie,' ',''),'-','')) else (select UPPER(REPLACE(REPLACE(RTA.valorAtributo,' ',''),'-','')) from reclamoTareasAtributos RTA where RTA.idReclamo=REC.idReclamo and RTA.idAtributo=17 limit 1) end "
                      "else UPPER(REPLACE(REPLACE(REC.numeroSerie,' ',''),'-','')) end'NumeroSerie', "
                      "REC.idCausa'CodigoCausa', "
                      "REPLACE(CAUS.denominacion,'\\'','')'NombreCausa',  "
                      "case when CAUS.atribuible=2 then 'SISTECO' when CAUS.atribuible=1 then 'Cliente/Tercero' else 'Otro' end'CausaAtribuible', "
                      "(select count(RECTAR.idReclamo) from reclamoTareas RECTAR where RECTAR.idReclamo=REC.idReclamo)'CantidadTareas', "
                      "0'TiempoEstadoNuevo',"
                      "REPLACE(REC.titulo,'\\'','')'TituloReclamo',  "
                      "PROD.idTipo'CodigoTipo',  "
                      "REPLACE(TIPO.denominacion,'\\'','')'NombreTipo',  "
                      "0'TiempoEsperaRespuestaClienteHorarioSisteco',"
                      "SUC.idDepartamento'CodigoDepartamento',  "
                      "REPLACE(DEP.denominacion,'\\'','')'NombreDepartamento',  "
                      "case when coordinado='N' then  case when  (CAUS.atribuible=2 and CAUS.idCausa=1)  then '1' else '0' end  else  '1'  end 'CodigoCoordinado', "
                      "case when coordinado='N' then  case when  (CAUS.atribuible=2 and CAUS.idCausa=1)  then 'Coordinado' else 'No coordinado' end  else 'Coordinado' end 'NombreCoordinado', "

                      "REPLACE(SUC.direccionFiscal,'\\'','')'DireccionSucursal',  "
                      "REPLACE(REC.reclamante,'\\'','')'NombreSolicitante',  "
                      "REPLACE(REC.firmoCierre,'\\'','')'NombreFirmoCierre',  "
                      "(SELECT RECBIT.hora from reclamoBitacora RECBIT where RECBIT.idReclamo=REC.idReclamo and RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)   else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) in (3,8) order by RECBIT.fecha, RECBIT.hora limit 1) as 'HoraFinalizacion', "
                      "(SELECT RECBIT.fecha from reclamoBitacora RECBIT where RECBIT.idReclamo=REC.idReclamo and RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)   else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) in (3,8) order by RECBIT.fecha, RECBIT.hora limit 1) as 'FechaFinalizacion', "
                      "case when CAUS.atribuible=2 then '' else REPLACE(REC.causaCliente,'\\'',' ')  end 'CausaDeCliente', "
                      "REC.idCamino'CodigoCamino', "
                      "REPLACE(CAM.denominacion,'\\'','')'NombreCamino',"
                      "REC.idRazon'CodigoSintoma',"
                      "case when REC.idRazon=0 then 'Sin síntoma' else REPLACE(RAZ.denominacion,'\\'','') end'NombreSintoma', "
                      "REC.idTipoReclamo'CodigoTipoReclamoCliente', "
                      "TIPOR.denominacion'NombreTipoReclamoCliente' "


                      "from reclamos REC join clientes CLI on CLI.idCliente=REC.idCliente "
                      "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal "
                      "join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                      "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable "
                      "join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado "
                      "join tipos TIPO on TIPO.idTipo=PROD.idTipo "
                      "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                      "join caminos CAM on CAM.idCamino=REC.idCamino "
                      "join tipoReclamos TIPOR on TIPOR.idTipoReclamo=REC.idTipoReclamo "
                      "left join razones RAZ on RAZ.idRazon=REC.idRazon "
                      "where REC.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"' and REC.idEstado in (3,5,7,8,13,15,18) "
                      "order by REC.idReclamo asc ";


    /*
                _insertsReclamos+=" "+query.value(rec.indexOf("CodigoTipoReclamoCliente")).toString()+",";
                _insertsReclamos+="'"+query.value(rec.indexOf("NombreTipoReclamoCliente")).toString()+"'";

                //codigoTipoReclamoCliente
                //nombreTipoReclamoCliente

*/


    /// Consulta para obtener las tareas
    _consultaTareas="select "
                    "REC.idReclamo'CodigoReclamo', "
                    "RECTAR.idTarea'CodigoTarea', "
                    "REPLACE(TAR.denominacion,'\\'','') 'NombreTarea',  "
                    "case when TAR.idTareaReporte=0 then REPLACE(TAR.denominacion,'\\'','') else REPLACE(TARREP.denominacion,'\\'','') end  'NombreTareaReporte',  "
                    "RECTAR.fecha'FechaTarea', "
                    "RECTAR.hora'HoraTarea', "
                    "REPLACE(RECTAR.comentarios,'\\'',' ') 'ComentariosTareas', "
                    "(RECTAR.horas*60)+(RECTAR.minutos) 'TiempoTarea' "
                    "from reclamos REC "
                    "join clientes CLI on CLI.idCliente=REC.idCliente "
                    "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal "
                    "join areas AREA on AREA.idArea=REC.idArea "
                    "join productos PROD on PROD.idProducto=REC.idProducto "
                    "join marcas MARC on MARC.idMarca=PROD.idMarca "
                    "join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable "
                    "join causas CAUS on CAUS.idCausa=REC.idCausa "
                    "join estados ESTA on ESTA.idEstado=REC.idEstado "
                    "join reclamoTareas RECTAR on RECTAR.idReclamo=REC.idReclamo "
                    "join tareas TAR on TAR.idTarea=RECTAR.idTarea "
                    "join tareasReporte TARREP on TARREP.idTareaReporte=TAR.idTareaReporte "
                    "join tipos TIPO on TIPO.idTipo=PROD.idTipo "
                    "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                    "join caminos CAM on CAM.idCamino=REC.idCamino "
                    "where REC.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"' and REC.idEstado in (3,5,7,8,13,15,18) "
                    "order by REC.idReclamo asc ";


    /// Consulta para obtener los conceptos
    _consultaConceptos="select "
                       "REC.idReclamo'CodigoReclamo',  "
                       "RECCON.idConcepto'CodigoConcepto', "
                       "REPLACE(CON.denominacion,'\\'','')'NombreConcepto' "
                       "from reclamos REC  "
                       "join reclamoConceptos RECCON on RECCON.idReclamo=REC.idReclamo "
                       "join conceptos CON on CON.idConcepto=RECCON.idConcepto "
                       "where REC.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"' and REC.idEstado in (3,5,7,8,13,15,18)  "
                       "order by REC.idReclamo asc ";



    /// Seteo  las consultas de tareas y reclamos
    ProcesarInformacion::setConsultaSqlRemotaReclamos(_consultaReclamos);
    ProcesarInformacion::setConsultaSqlRemotaTareas(_consultaTareas);
    ProcesarInformacion::setConsultaSqlRemotaConceptos(_consultaConceptos);
}

bool ProcesarInformacion::cargoDatosReclamosTiempos(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        ////////Cargo la información de tiempo en estado nuevo
        if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoNuevo1 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                      "SELECT RECBIT.idReclamo, case when RECBIT.idOperacion in (13,19) then concat(RECBIT.fecha,' ',RECBIT.hora) else "
                      "case when (RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                      "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=4 "
                      ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end  end'Hora Guardado', "
                      "case when (RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                      "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=2 "
                      ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end 'Hora cambio estado', "
                      "case when RECBIT.idOperacion in (13,19) or (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                      "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=4 then 1 else 0 end'estado', "
                      "RECBIT.correlativo "
                      "FROM reclamoBitacora RECBIT join reclamos REC on REC.idReclamo=RECBIT.idReclamo join clientes CLI on CLI.idCliente=REC.idCliente  "
                      "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                      "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado "
                      "join tipos TIPO on TIPO.idTipo=PROD.idTipo "
                      "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                      "join caminos CAM on CAM.idCamino=REC.idCamino "
                      "where   REC.idEstado in (3,5,7,8,13,15,18) and RECBIT.idOperacion in (10,13,19) and RECBIT.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'"
                      "order by RECBIT.idReclamo asc, RECBIT.fecha asc, RECBIT.hora asc;"
                      )){

            if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoNuevo2 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                          "select  codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo from tabla_EstadoNuevo1  "
                          "where !(horaGuardado='0' and horaCambioEstado='0' and estado='0'); ")){

                if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoNuevo (codigoReclamo,horaGuardado,horaCambioEstado) "
                              "select  TEMP2.codigoReclamo, TEMP2.horaGuardado, case when TEMP2.estado='1' "
                              "then (select TEMP3.horaCambioEstado from tabla_EstadoNuevo1 TEMP3 where TEMP3.estado='0' and TEMP3.horaGuardado='0' and TEMP3.codigoReclamo=TEMP2.codigoReclamo and TEMP3.horaCambioEstado>=TEMP2.horaGuardado limit 1) else 0 end "
                              "from tabla_EstadoNuevo2 TEMP2; ")){





                    ////////Cargo la información de tiempo en estado asignado
                    if(query.exec("SET SQL_MODE=''; INSERT INTO tabla_EstadoAsignado1 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                  "SELECT distinct RECBIT.idReclamo, "
                                  "case when RECBIT.idOperacion in (9) then concat(RECBIT.fecha,' ',RECBIT.hora) else  "
                                  "case when (RECBIT.idOperacion=10 and  "
                                  "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                  "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) "
                                  "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)in (2,9) "
                                  ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end  end'Hora Guardado', "
                                  "case when (RECBIT.idOperacion=10 and "
                                  "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                  "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) "
                                  "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) not in (2,5,7) "
                                  ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end 'Hora cambio estado',"
                                  //  "case when RECBIT.idOperacion in (9) or  "
                                  "case when  "
                                  "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                  "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) "
                                  "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)in (2,9) then 1 else 0 end'estado', "
                                  "RECBIT.correlativo "
                                  "FROM reclamoBitacora RECBIT join reclamos REC on REC.idReclamo=RECBIT.idReclamo join clientes CLI on CLI.idCliente=REC.idCliente  "
                                  "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                                  "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado "
                                  "join tipos TIPO on TIPO.idTipo=PROD.idTipo "
                                  "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                                  "join caminos CAM on CAM.idCamino=REC.idCamino "
                                  "where   REC.idEstado in (3,5,7,8,13,15,18) and RECBIT.idOperacion in (10,9)  and RECBIT.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'"
                                  "order by RECBIT.idReclamo asc, RECBIT.fecha asc, RECBIT.hora asc; "
                                  )){

                        if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoAsignado2 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                      "select  codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo  from tabla_EstadoAsignado1  "
                                      "where !(horaGuardado='0' and horaCambioEstado='0' and estado='0'); ")){

                            if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoAsignado (codigoReclamo,horaGuardado,horaCambioEstado) "
                                          "select  TEMP2.codigoReclamo, TEMP2.horaGuardado, case when TEMP2.estado='1' "
                                          "then (select TEMP3.horaCambioEstado from tabla_EstadoAsignado1 TEMP3 where TEMP3.estado='0' and TEMP3.horaGuardado='0' and TEMP3.codigoReclamo=TEMP2.codigoReclamo and TEMP3.horaCambioEstado>=TEMP2.horaGuardado  limit 1) else 0 end "
                                          "from tabla_EstadoAsignado2 TEMP2; ")){



                                ///quito la operacion 9 para corregir problema de tiempos, esto esta a prueba   ") or RECBIT.idOperacion=9 then concat(RECBIT.fecha,' ',RECBIT.hora)  else '0' end 'Hora cambio estado', "

                                ////////Cargo la información de tiempo esperando respuesta de cliente
                                if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaCliente1 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                              "SELECT distinct RECBIT.idReclamo, "
                                              "case when (RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                              "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                              "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=6 "
                                              ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end 'Hora Guardado', "
                                              "case when (RECBIT.idOperacion in (10) and "
                                              "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<'  "
                                              "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                              "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) not in (6)  "
                                              ")  then concat(RECBIT.fecha,' ',RECBIT.hora)  else '0' end 'Hora cambio estado', "
                                              "case when RECBIT.idOperacion in (10) and "
                                              "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<'  "
                                              "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                              "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=6  "
                                              "then 1 else 0 end'estado', "
                                              "RECBIT.correlativo "
                                              "FROM reclamoBitacora RECBIT join reclamos REC on REC.idReclamo=RECBIT.idReclamo join clientes CLI on CLI.idCliente=REC.idCliente   "
                                              "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                                              "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado  "
                                              "join tipos TIPO on TIPO.idTipo=PROD.idTipo  "
                                              "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                                              "join caminos CAM on CAM.idCamino=REC.idCamino "
                                              "where   REC.idEstado in (3,5,7,8,13,15,18) and RECBIT.idOperacion in (10,9) and RECBIT.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'"
                                              "order by RECBIT.idReclamo asc ,RECBIT.correlativo asc, RECBIT.fecha asc, RECBIT.hora asc; "
                                              )){

                                    if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaCliente2 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                                  "select  codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo  from tabla_EsperaCliente1  "
                                                  "where !(horaGuardado='0' and horaCambioEstado='0' and estado='0'); ")){

                                        if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaCliente (codigoReclamo,horaGuardado,horaCambioEstado) "
                                                      "select  TEMP2.codigoReclamo, TEMP2.horaGuardado, case when TEMP2.estado='1' "
                                                      "then (select TEMP3.horaCambioEstado from tabla_EsperaCliente1 TEMP3 where TEMP3.estado='0' and TEMP3.horaGuardado='0' and TEMP3.codigoReclamo=TEMP2.codigoReclamo and TEMP3.horaCambioEstado>=TEMP2.horaGuardado and TEMP3.correlativo>TEMP2.correlativo limit 1) else 0 end "
                                                      "from tabla_EsperaCliente2 TEMP2; ")){



                                            ////////Cargo la información de tiempo esperando respuesta de objetos
                                            if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaObjetos1 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                                          "SELECT distinct RECBIT.idReclamo, "
                                                          "case when (RECBIT.idOperacion=10 and (case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                                          "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                                          "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=11 "
                                                          ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end 'Hora Guardado', "
                                                          "case when (RECBIT.idOperacion in (10) and "
                                                          "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<'  "
                                                          "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                                          "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) not in (11)  "
                                                          ") or RECBIT.idOperacion=9 then concat(RECBIT.fecha,' ',RECBIT.hora)  else '0' end 'Hora cambio estado', "
                                                          "case when RECBIT.idOperacion in (10) and "
                                                          "(case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<'  "
                                                          "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2)  "
                                                          "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end)=11  "
                                                          "then 1 else 0 end'estado', "
                                                          "RECBIT.correlativo "
                                                          "FROM reclamoBitacora RECBIT join reclamos REC on REC.idReclamo=RECBIT.idReclamo join clientes CLI on CLI.idCliente=REC.idCliente   "
                                                          "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                                                          "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado  "
                                                          "join tipos TIPO on TIPO.idTipo=PROD.idTipo  "
                                                          "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                                                          "join caminos CAM on CAM.idCamino=REC.idCamino "
                                                          "where   REC.idEstado in (3,5,7,8,13,15,18) and RECBIT.idOperacion in (10) and RECBIT.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'"
                                                          "order by RECBIT.idReclamo asc ,RECBIT.correlativo asc, RECBIT.fecha asc, RECBIT.hora asc; "
                                                          )){

                                                if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaObjetos2 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                                              "select  codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo  from tabla_EsperaObjetos1  "
                                                              "where !(horaGuardado='0' and horaCambioEstado='0' and estado='0'); ")){

                                                    if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EsperaObjetos (codigoReclamo,horaGuardado,horaCambioEstado) "
                                                                  "select  TEMP2.codigoReclamo, TEMP2.horaGuardado, case when TEMP2.estado='1' "
                                                                  "then (select TEMP3.horaCambioEstado from tabla_EsperaObjetos1 TEMP3 where TEMP3.estado='0' and TEMP3.horaGuardado='0' and TEMP3.codigoReclamo=TEMP2.codigoReclamo and TEMP3.horaCambioEstado>=TEMP2.horaGuardado and TEMP3.correlativo>TEMP2.correlativo limit 1) else 0 end "
                                                                  "from tabla_EsperaObjetos2 TEMP2; ")){



                                                        ////////Cargo la información de tiempo total
                                                        if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoTotal1 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                                                      "SELECT RECBIT.idReclamo, "
                                                                      "case when RECBIT.idOperacion in (13,19) then concat(RECBIT.fecha,' ',RECBIT.hora) else  '0' end 'Hora Guardado', "
                                                                      "case when ((case when right(left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2),1)!='<' "
                                                                      "then left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),2) "
                                                                      "else left((SUBSTRING(RECBIT.comentarios,(LOCATE('<EstadoNuevo>', RECBIT.comentarios)+13))),1) end) in (3,8) "
                                                                      ") then concat(RECBIT.fecha,' ',RECBIT.hora) else '0' end 'Hora cambio estado', "
                                                                      "case when RECBIT.idOperacion in (13,19) then  1 else 0 end'estado', "
                                                                      "RECBIT.correlativo "
                                                                      "FROM reclamoBitacora RECBIT join reclamos REC on REC.idReclamo=RECBIT.idReclamo join clientes CLI on CLI.idCliente=REC.idCliente  "
                                                                      "join sucursales SUC on SUC.idCliente=CLI.idCliente and SUC.idSucursal=REC.idSucursal join areas AREA on AREA.idArea=REC.idArea join productos PROD on PROD.idProducto=REC.idProducto "
                                                                      "join marcas MARC on MARC.idMarca=PROD.idMarca join funcionarios FUNC on FUNC.idFuncionario=REC.idResponsable join causas CAUS on CAUS.idCausa=REC.idCausa join estados ESTA on ESTA.idEstado=REC.idEstado "
                                                                      "join tipos TIPO on TIPO.idTipo=PROD.idTipo  "
                                                                      "join departamentos DEP on DEP.idDepartamento=SUC.idDepartamento "
                                                                      "join caminos CAM on CAM.idCamino=REC.idCamino "
                                                                      "where   REC.idEstado in (3,5,7,8,13,15,18) and RECBIT.idOperacion in (10,13,19) and RECBIT.idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"'"
                                                                      "order by RECBIT.idReclamo asc, RECBIT.fecha asc, RECBIT.hora asc; "
                                                                      )){

                                                            if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoTotal2 (codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo) "
                                                                          "select  codigoReclamo,horaGuardado,horaCambioEstado,estado,correlativo  from tabla_EstadoTotal1  "
                                                                          "where !(horaGuardado='0' and horaCambioEstado='0' and estado='0'); ")){

                                                                if(query.exec("SET SQL_MODE='';INSERT INTO tabla_EstadoTotal (codigoReclamo,horaGuardado,horaCambioEstado) "
                                                                              "select  TEMP2.codigoReclamo, TEMP2.horaGuardado, case when TEMP2.estado='1' "
                                                                              "then (select TEMP3.horaCambioEstado from tabla_EstadoTotal1 TEMP3 where TEMP3.estado='0' and TEMP3.horaGuardado='0' and TEMP3.codigoReclamo=TEMP2.codigoReclamo and TEMP3.horaCambioEstado>=TEMP2.horaGuardado    and TEMP3.correlativo>TEMP2.correlativo    order by TEMP3.horaCambioEstado desc limit 1) else 0 end "
                                                                              "from tabla_EstadoTotal2 TEMP2; ")){
                                                                    return true;

                                                                }else{
                                                                    Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoTotal" );
                                                                    Logs::loguear(query.lastError().text());
                                                                    return false;}
                                                            }else{
                                                                Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoTotal2" );
                                                                Logs::loguear(query.lastError().text());
                                                                return false;}
                                                        }else{
                                                            Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoTotal1" );
                                                            Logs::loguear(query.lastError().text());
                                                            return false;}
                                                    }else{
                                                        Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaObjetos" );
                                                        Logs::loguear("Insert: "+query.executedQuery());
                                                        Logs::loguear(query.lastError().text());
                                                        return false;}
                                                }else{
                                                    Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaObjetos2" );
                                                    Logs::loguear("Insert: "+query.executedQuery());
                                                    Logs::loguear(query.lastError().text());
                                                    return false;}
                                            }else{
                                                Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaObjetos1" );
                                                Logs::loguear("Insert: "+query.executedQuery());
                                                Logs::loguear(query.lastError().text());
                                                return false;}
                                        }else{
                                            Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaCliente" );
                                            Logs::loguear("Insert: "+query.executedQuery());
                                            Logs::loguear(query.lastError().text());
                                            return false;}
                                    }else{
                                        Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaCliente2" );
                                        Logs::loguear("Insert: "+query.executedQuery());
                                        Logs::loguear(query.lastError().text());
                                        return false;}
                                }else{
                                    Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EsperaCliente1" );
                                    Logs::loguear("Insert: "+query.executedQuery());
                                    Logs::loguear(query.lastError().text());
                                    return false;}

                            }else{
                                Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoAsignado" );
                                Logs::loguear("Insert: "+query.executedQuery());
                                Logs::loguear(query.lastError().text());
                                return false;}
                        }else{
                            Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoAsignado2" );
                            Logs::loguear("Insert: "+query.executedQuery());
                            Logs::loguear(query.lastError().text());
                            return false;}
                    }else{
                        Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoAsignado1" );
                        Logs::loguear("Insert: "+query.executedQuery());
                        Logs::loguear(query.lastError().text());
                        return false;}
                }else{

                    Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoNuevo" );
                    Logs::loguear("Insert: "+query.executedQuery());
                    Logs::loguear(query.lastError().text());
                    return false;}
            }else{
                Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoNuevo2" );
                Logs::loguear("Insert: "+query.executedQuery());
                Logs::loguear(query.lastError().text());
                return false;}
        }else{
            Logs::loguear("Función cargoDatosReclamosTiempos::INSERT INTO tabla_EstadoNuevo1" );
            Logs::loguear("Insert: "+query.executedQuery());
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}

bool ProcesarInformacion::prepararReclamosParaCalcularTiempos(){

    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        ////////////////////////////////////////////////
        ///Guardo tiempo en estado nuevo de un reclamo
        ////////////////////////////////////////////////
        QSqlQuery query(Database::connect("remoto"));
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EstadoNuevo where horaGuardado!=0 and horaCambioEstado!=0")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(!guardaTiempoEnEstadoNuevo(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString())))
                    return false;
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EstadoNuevo" );
            Logs::loguear(query.lastError().text());
            return false;
        }

        /////////////////////////////////////////
        ///Guardo tiempo asignado de un reclamo
        /////////////////////////////////////////
        query.clear();
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EstadoAsignado where horaGuardado!=0 and horaCambioEstado!=0")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(!guardaTiempoEnEstadoAsignado(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString())))
                    return false;
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EstadoAsignado" );
            Logs::loguear(query.lastError().text());
            return false;
        }

        /////////////////////////////////////////
        ///Guardo tiempo espera cliente
        /////////////////////////////////////////
        query.clear();
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EsperaCliente where horaGuardado!=0 and horaCambioEstado!=0")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(guardaTiempoEnEstadoEsperaRespuestaCliente(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString()))){
                    if(!guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString())))
                        return false;
                }else{return false;}
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EsperaCliente" );
            Logs::loguear(query.lastError().text());
            return false;
        }


        /////////////////////////////////////////
        ///Guardo tiempo espera objetos
        /////////////////////////////////////////
        query.clear();
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EsperaObjetos where horaGuardado!=0 and horaCambioEstado!=0")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(!guardaTiempoEnEstadoEsperaRespuestaObjetos(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString())))
                    return false;
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EsperaObjetos" );
            Logs::loguear(query.lastError().text());
            return false;
        }

        /////////////////////////////////////////
        ///Guardo tiempo de tareas en reclamo
        /////////////////////////////////////////
        query.clear();
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EstadoNuevo")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(!guardaTiempoTareaEnReclamo(query.value(rec.indexOf("codigoReclamo")).toString()))
                    return false;
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EstadoNuevo tareas" );
            Logs::loguear(query.lastError().text());
            return false;
        }

        /////////////////////////////////////////
        ///Guardo tiempo total del reclamo
        /////////////////////////////////////////
        query.clear();
        if(query.exec("SELECT distinct codigoReclamo FROM tabla_EstadoTotal where horaGuardado!=0 and horaCambioEstado!=0")){
            QSqlRecord rec = query.record();
            while(query.next()){
                if(!guardaTiempoTotalDeReclamo(query.value(rec.indexOf("codigoReclamo")).toString(),retornaTipoReclamo(query.value(rec.indexOf("codigoReclamo")).toString())))
                    return false;
            }
        }else{
            Logs::loguear("Función prepararReclamosParaCalcularTiempos::tabla_EstadoTotal" );
            Logs::loguear(query.lastError().text());
            return false;
        }

        return true;
    }else{
        return false;
    }
}

bool ProcesarInformacion::guardaTiempoEnEstadoNuevo(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EstadoNuevo where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){

            QSqlRecord rec = query.record();

            while(query.next()){

                QDateTime _tiempoGuardado;

                if(_tipoReclamo=="Comun" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){
                    // Si el tiempo a comparar es del mismo día, agrego los minutos
                    if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")==
                       _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                        }else{

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18)
                                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                            }
                        }

                    }else{
                        int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){

                            minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;

                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                               _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){




                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                                }else{

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                                }



                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{

                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }else if(_tipoReclamo=="Guardia" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){


                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;

                }
                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";
            }

            if(!actualizarReclamoTiempoEstadoNuevo(_codigoReclamo,minutosDelReclamo)){
                Logs::loguear("Función guardaTiempoEnEstadoNuevo::tabla_EstadoNuevo == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoEnEstadoNuevo::tabla_EstadoNuevo == Minutos a grabar: "+minutosDelReclamo);
                return false;
            }


            return true;
        }else{
            Logs::loguear("Función guardaTiempoEnEstadoNuevo::tabla_EstadoNuevo == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}


bool ProcesarInformacion::guardaTiempoEnEstadoAsignado(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EstadoAsignado where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){

            QSqlRecord rec = query.record();

            while(query.next()){

                QDateTime _tiempoGuardado;

                if(_tipoReclamo=="Comun" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){
                    // Si el tiempo a comparar es del mismo día, agrego los minutos
                    if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")==
                       _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                        }else{

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18)
                                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                            }
                        }





                    }else{
                        int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;
                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                               _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;
                                }else{

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                                }


                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{
                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }else if(_tipoReclamo=="Guardia" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){


                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;
                }
                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";

            }


            if(!actualizarReclamoTiempoEstadoAsignado(_codigoReclamo,minutosDelReclamo)){
                Logs::loguear("Función guardaTiempoEnEstadoAsignado::tabla_EstadoAsignado == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoEnEstadoAsignado::tabla_EstadoAsignado == Minutos a grabar: "+minutosDelReclamo);
                return false;
            }
            return true;
        }else{
            Logs::loguear("Función guardaTiempoEnEstadoAsignado::tabla_EstadoAsignado == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}

bool ProcesarInformacion::guardaTiempoEnEstadoEsperaRespuestaCliente(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EsperaCliente where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){
            QSqlRecord rec = query.record();

            while(query.next()){
                QDateTime _tiempoGuardado;

                if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;

                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";
            }
            if(!actualizarReclamoTiempoEstadoEsperaRespuestaCliente(_codigoReclamo,minutosDelReclamo)){
                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaCliente::tabla_EsperaCliente == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaCliente::tabla_EsperaCliente == Minutos a grabar: "+minutosDelReclamo);
                return false;
            }

            return true;
        }else{
            Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaCliente::tabla_EsperaCliente == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}
bool ProcesarInformacion::guardaTiempoEnEstadoEsperaRespuestaObjetos(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EsperaObjetos where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){

            QSqlRecord rec = query.record();

            while(query.next()){

                QDateTime _tiempoGuardado;

                if(_tipoReclamo=="Comun" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){
                    // Si el tiempo a comparar es del mismo día, agrego los minutos
                    if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")==
                       _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){
                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                        }else{
                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18)
                                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                            }
                        }



                    }else{
                        int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){

                            minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;
                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                               _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){
                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                                }else{
                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;


                                }
                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{
                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }else if(_tipoReclamo=="Guardia" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){


                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;

                }
                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";
            }

            if(!actualizarReclamoTiempoEstadoEsperaObjetos(_codigoReclamo,minutosDelReclamo)){

                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaObjetos::tabla_EsperaObjetos == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaObjetos::tabla_EsperaObjetos == Minutos a grabar: "+minutosDelReclamo);
                return false;

            }

            return true;
        }else{
            Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaObjetos::tabla_EsperaObjetos == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}
bool ProcesarInformacion::guardaTiempoTareaEnReclamo(QString _codigoReclamo){

    qlonglong minutosDelReclamo=0;
    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("SELECT sum(tiempoTarea)'tiempoT' FROM Tareas where idReclamo="+_codigoReclamo+" and tiempoTarea!=0")){
            QSqlRecord rec = query.record();

            if(query.first()){
                minutosDelReclamo=query.value(rec.indexOf("tiempoT")).toLongLong();

                if(!actualizarReclamoTiempoTareas(_codigoReclamo,minutosDelReclamo)){
                    Logs::loguear("Función guardaTiempoTareaEnReclamo::Tareas == Reclamo: "+_codigoReclamo);
                    Logs::loguear("Función guardaTiempoTareaEnReclamo::Tareas == Minutos a grabar: "+minutosDelReclamo);
                    return false;
                }
            }
            return true;
        }else{
            Logs::loguear("Función guardaTiempoTareaEnReclamo::Tareas == Reclamo: "+_codigoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}

bool ProcesarInformacion::guardaTiempoTotalDeReclamo(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EstadoTotal where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){

            QSqlRecord rec = query.record();

            while(query.next()){

                QDateTime _tiempoGuardado;


                if(_tipoReclamo=="Comun" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){
                    // Si el tiempo a comparar es del mismo día, agrego los minutos
                    if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")==
                       _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                        }else{

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18)
                                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                            }

                        }


                    }else{
                        int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){
                            minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;

                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                               _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){

                                if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                    minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{

                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                                        i++;

                                    }
                                }
                            }
                        }
                    }
                }else if(_tipoReclamo=="Guardia" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){

                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;

                }
                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";
            }

            if(!actualizarReclamoTiempoTotalDeReclamo(_codigoReclamo,minutosDelReclamo)){
                Logs::loguear("Función guardaTiempoTotalDeReclamo::tabla_EstadoTotal == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoTotalDeReclamo::tabla_EstadoTotal == Minutos a grabar: "+minutosDelReclamo);
                return false;
            }
            return true;
        }else{
            Logs::loguear("Función guardaTiempoTotalDeReclamo::tabla_EstadoTotal == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}
bool ProcesarInformacion::guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco(QString _codigoReclamo,QString _tipoReclamo){

    qlonglong minutosDelReclamo=0;
    QString horaCambioEstadoAnterior="";
    bool conexion=true;
    if(!Database::connect("remoto").isOpen()){
        if(!Database::connect("remoto").open()){

            Logs::loguear("No hay conexion a la base de datos de madai");
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect("remoto"));

        if(query.exec("SELECT * FROM tabla_EsperaCliente where codigoReclamo="+_codigoReclamo+" and horaGuardado!=0 and horaCambioEstado!=0 ")){

            QSqlRecord rec = query.record();

            while(query.next()){

                QDateTime _tiempoGuardado;

                if(_tipoReclamo=="Comun" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){
                    // Si el tiempo a comparar es del mismo día, agrego los minutos
                    if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")==
                       _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                        }else{

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior){

                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18)
                                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                            }
                        }


                    }else{
                        /*int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){
                            minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;

                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                                    _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){

                                if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                    minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;

                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{

                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;

                                        i++;
                                    }
                                }
                            }
                        }*/
                        int i=1;

                        if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time()<QTime(18,0,0,0)){

                            if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").time().secsTo(QTime(18,0,0,0))/60;
                        }

                        while(i!=9999){

                            if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd")==
                               _tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date().toString("yyyy-MM-dd")){


                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time().hour()<18){

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").time())/60;
                                }else{

                                    if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                        minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                                }


                                i=9999;

                            }else{
                                if(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==6 || _tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).dayOfWeek()==7){
                                    i++;
                                }else{

                                    if(ProcesarInformacion::esUnDiaFeriadoFijo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date().addDays(i).toString("yyyy-MM-dd"))){
                                        i++;
                                    }else{
                                        if(query.value(rec.indexOf("horaCambioEstado")).toString()!=horaCambioEstadoAnterior)
                                            minutosDelReclamo+=QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(9,0,0,0)).addDays(i).time().secsTo(QDateTime(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm").date(),QTime(18,0,0,0)).time())/60;
                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }else if(_tipoReclamo=="Guardia" && !retornaSiEsReclamoCoordinado(_codigoReclamo)){


                    minutosDelReclamo+=_tiempoGuardado.fromString(query.value(rec.indexOf("horaGuardado")).toString(),"yyyy-MM-dd HH:mm").secsTo(_tiempoGuardado.fromString(query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm"))/60;

                }
                horaCambioEstadoAnterior=query.value(rec.indexOf("horaCambioEstado")).toString(),"yyyy-MM-dd HH:mm";
            }

            if(!actualizarReclamoTiempoEstadoEsperaRespuestaClienteHorarioSisteco(_codigoReclamo,minutosDelReclamo)){

                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco::tabla_EsperaCliente == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
                Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco::tabla_EsperaCliente == Minutos a grabar: "+minutosDelReclamo);
                return false;}

            return true;
        }else{
            Logs::loguear("Función guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco::tabla_EsperaCliente == Reclamo: "+_codigoReclamo +" -Tipo Reclamo: "+_tipoReclamo);
            Logs::loguear(query.lastError().text());
            return false;
        }
    }else{
        return false;
    }
}

bool ProcesarInformacion::esUnDiaFeriadoFijo(QString _fechaAcomparar){
    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("SELECT * FROM Feriados where codigoMes=0 and codigoAnio=0 and fechaFeriado='"+QDate::fromString(_fechaAcomparar,"yyyy-MM-dd").toString("dd-MM")+"'")){

            if(query.first()){
                if(query.value(0).toString()!=""){
                    return true;
                }else{
                    Logs::loguear("Función: esUnDiaFeriadoFijo == Fecha a comparar: "+_fechaAcomparar);
                    Logs::loguear(query.lastError().text());
                    return false;
                }
            }else{
                return false;
            }
        }else{
            Logs::loguear( "Función: esUnDiaFeriadoFijo::Feriados == Fecha a comparar: "+_fechaAcomparar);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
QString ProcesarInformacion::retornaTipoReclamo(QString _codigoReclamo){
    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("SELECT nombreTipoReclamo FROM Reclamos where codigoReclamo='"+_codigoReclamo+"'")){

            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "Comun";
                }
            }else{
                Logs::loguear( "Función: retornaTipoReclamo::query.first() == Reclamo: "+_codigoReclamo);
                Logs::loguear(query.lastError().text());
                return "Comun";
            }
        }else{
            Logs::loguear( "Función: retornaTipoReclamo == Reclamo: "+_codigoReclamo);
            Logs::loguear(query.lastError().text());
            return "Comun";}
    }else{return "Comun";}
}

bool ProcesarInformacion::retornaSiEsReclamoCoordinado(QString _codigoReclamo){
    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("SELECT codigoCoordinado FROM Reclamos where codigoReclamo='"+_codigoReclamo+"'")){

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.value(0).toString()=="0"){
                        return false;
                    }else{
                        return true;
                    }
                }else{
                    return false;
                }
            }else{
                Logs::loguear( "Función: retornaSiEsReclamoCoordinado::query.first() == Reclamo: "+_codigoReclamo);
                Logs::loguear(query.lastError().text());
                return false;
            }
        }else{
            Logs::loguear( "Función: retornaSiEsReclamoCoordinado == Reclamo: "+_codigoReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoEstadoNuevo(QString _codigoReclamo,qlonglong _minutosReclamo){


    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoEstadoNuevo='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear( "Función: actualizarReclamoTiempoEstadoNuevo == Reclamo:" +_codigoReclamo +" -Minutos Reclamo: " +_minutosReclamo);
            Logs::loguear(query.lastError().text());

            return false;
        }
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoEstadoAsignado(QString _codigoReclamo,qlonglong _minutosReclamo){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoEstadoAsignado='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear("Función: actualizarReclamoTiempoEstadoAsignado == Reclamo: "+_codigoReclamo + " - Minutos Reclamo: "+_minutosReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoEstadoEsperaRespuestaCliente(QString _codigoReclamo,qlonglong _minutosReclamo){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoEsperaRespuestaCliente='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear("Función: actualizarReclamoTiempoEstadoEsperaRespuestaCliente == Reclamo: "+_codigoReclamo + " - Minutos Reclamo: "+_minutosReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoEstadoEsperaObjetos(QString _codigoReclamo,qlonglong _minutosReclamo){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoEsperaRespuestaObjetos='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear("Función: actualizarReclamoTiempoEstadoEsperaObjetos == Reclamo: "+_codigoReclamo + " - Minutos Reclamo: "+_minutosReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoTareas(QString _codigoReclamo,qlonglong _minutosReclamo){


    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoTareas='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear( "Función: actualizarReclamoTiempoTareas == Reclamo: "+_codigoReclamo + " - Minutos Reclamo: "+_minutosReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoTotalDeReclamo(QString _codigoReclamo,qlonglong _minutosReclamo){


    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoResolucion="+QString::number(_minutosReclamo)+"-tiempoEsperaRespuestaClienteHorarioSisteco  where codigoReclamo='"+_codigoReclamo+"'")){
            return true;

        }else{
            Logs::loguear( "Función: actualizarReclamoTiempoTotalDeReclamo == Reclamo:" +_codigoReclamo +" -Minutos Reclamo: " +_minutosReclamo);
            Logs::loguear(query.lastError().text());

            return false;}
    }else{return false;}
}
bool ProcesarInformacion::actualizarReclamoTiempoEstadoEsperaRespuestaClienteHorarioSisteco(QString _codigoReclamo,qlonglong _minutosReclamo){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){

            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("UPDATE Reclamos SET tiempoEsperaRespuestaClienteHorarioSisteco='"+QString::number(_minutosReclamo)+"' where codigoReclamo='"+_codigoReclamo+"'")){

            return true;

        }else{
            Logs::loguear( "Función: actualizarReclamoTiempoEstadoEsperaRespuestaClienteHorarioSisteco == Reclamo: "+_codigoReclamo + " - Minutos Reclamo: "+_minutosReclamo);
            Logs::loguear(query.lastError().text());
            return false;}
    }else{return false;}
}
QString ProcesarInformacion::retornaReclamoDondeEmpezarABorrar(QString _modo, int _cantidadMesesABorrar){

    bool conexion=true;
    if(!Database::connect("local").isOpen()){
        if(!Database::connect("local").open()){
            Logs::loguear("No hay conexion a la base de datos almacen");
            conexion=false;
        }
    }
    if(_cantidadMesesABorrar==0){
        _cantidadMesesABorrar=-500;
    }else{
        _cantidadMesesABorrar=_cantidadMesesABorrar*-1;
    }

    if(conexion){
        QSqlQuery query(Database::connect("local"));

        if(query.exec("SELECT codigoReclamo FROM Reclamos where fechaCompletaReclamo like '"+QDate::currentDate().addMonths(_cantidadMesesABorrar).toString("yyyy-MM")+"%'  order by codigoReclamo desc limit 1")){

            if(query.first()){
                if(query.value(0).toString()!=""){
                    ProcesarInformacion::setReclamoDesdeDondeEmpezarABorrar(query.value(0).toString());
                    return query.value(0).toString();
                }else{
                    Logs::loguear( "Función: retornaReclamoDondeEmpezarABorrar::query.first().toString()::modo: "+_modo);
                    Logs::loguear(query.lastError().text());
                    Logs::loguear("Se retorna el reclamo numero 0, no hay registros en la base de datos.");
                    ProcesarInformacion::setReclamoDesdeDondeEmpezarABorrar("0");
                    return "0";
                }
            }else{
                Logs::loguear( "Función: retornaReclamoDondeEmpezarABorrar::query.first()::modo: "+_modo);
                Logs::loguear(query.lastError().text());
                Logs::loguear("Se retorna el reclamo numero 0, la conuslta fallo, no hay registros en la base de datos, o se requiere la carga completa.");
                ProcesarInformacion::setReclamoDesdeDondeEmpezarABorrar("0");
                return "0";
            }
        }else{
            Logs::loguear( "Función: retornaReclamoDondeEmpezarABorrar::query::modo: "+_modo);
            Logs::loguear(query.lastError().text());
            Logs::loguear("Se retorna el reclamo numero 0, la conuslta fallo, o no hay registros en la base de datos.");
            ProcesarInformacion::setReclamoDesdeDondeEmpezarABorrar("0");
            return "0";}
    }else{
        Logs::loguear("Función: retornaReclamoDondeEmpezarABorrar::conexion: "+_modo);
        Logs::loguear("Se retorna el reclamo numero 0, no hay conexión con la base de datos.");
        ProcesarInformacion::setReclamoDesdeDondeEmpezarABorrar("0");
        return "0";}
}

////////////////////////////////////////////////////////////////////////////////////
///Recavar información de reclamos que no van a cargarse segun criterios de campos//
////////////////////////////////////////////////////////////////////////////////////
void ProcesarInformacion::recavarReclamosQueNoSeCargan(){

    QString reclamosAInformar="echo -e \"Reclamos que no se cargaron en la base de datos almacen\\n\\n";

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){
            Logs::loguear("No hay conexion a la base de datos madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));

        ///Consulta por todos los reclamos que no tienen idCausa
        if(query.exec("select idReclamo from reclamos where idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"' and idCausa is null and idEstado in (3,5,7,13)")){
            if(query.first()){
                query.previous();
                reclamosAInformar.append("Reclamos sin CAUSA: ");
                while(query.next())
                {
                    reclamosAInformar.append("\\n* "+query.value(0).toString());
                }
                reclamosAInformar.append("\"| mail -s \"Cargador base de datos almacen: informe diario "+QDate::currentDate().toString("dd-MM-yyyy")+"\" jvila@sisteco.com.uy,gzipitria@sisteco.com.uy,cmontano@sisteco.com.uy");
                if(ProcesarInformacion::EjectuarComando(reclamosAInformar)==0)
                {
                    Logs::loguear( "Informe diario de reclamos no cargados enviado correctamente ");
                }else{
                    Logs::loguear( "Función: recavarReclamosQueNoSeCargan == No se pudo enviar el informe por mail ");
                }
            }else{                
                Logs::loguear( "Función: recavarReclamosQueNoSeCargan == No hay reclamos sin causa para mostrar ");
            }
        }else{
            Logs::loguear( "Función: recavarReclamosQueNoSeCargan == SELECT idCausa ");
            Logs::loguear(query.lastError().text());
        }
    }else{
        Logs::loguear("Función: recavarReclamosQueNoSeCargan::conexion: No hay conexion disponible");
    }
}


/////////
//Funcion para ejecutar comandos por consola
/////////
int ProcesarInformacion::EjectuarComando(QString comando){
    QStringList arg;
    QProcess procesos;
    QString p = "bash";
    arg << "-c"<< comando;
    int ok = procesos.execute(p,arg);
    return ok;
}


/////////
// Informe de error en la carga de almacen
/////////
void ProcesarInformacion::informeDeCargaDeDatosAlmacen(QString _mensaje){

    QString reclamosAInformar="echo -e \""+_mensaje+" \\n\\n";

    reclamosAInformar.append("\"| mail -s \"Cargador base de datos almacen: informe de << ERROR >> "+QDate::currentDate().toString("dd-MM-yyyy")+"\" jvila@sisteco.com.uy,gzipitria@sisteco.com.uy,cmontano@sisteco.com.uy");
    if(ProcesarInformacion::EjectuarComando(reclamosAInformar)==0)
    {
        Logs::loguear( "Informe de << ERROR >> enviado correctamente ");
    }else{
        Logs::loguear( "Función: informeDeCargaDeDatosAlmacen == No se pudo enviar el informe de error por mail ");
    }



}


void ProcesarInformacion::reclamosAlosCualesHayQueAsignarCausaYSintoma(){

    bool conexion=true;
    if(!Database::connect("remota").isOpen()){
        if(!Database::connect("remota").open()){
            Logs::loguear("No hay conexion a la base de datos madai");
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect("remota"));
        QSqlQuery query2(Database::connect("remota"));

        ///Consulta por todos los reclamos que no tienen idCausa
        if(query.exec("select idReclamo from reclamos where idReclamo>'"+ProcesarInformacion::getReclamoDesdeDondeEmpezarABorrar()+"' and idCausa is null and idEstado=18")){
            if(query.first()){
                query.previous();

                while(query.next())
                {
                    if(query2.exec("UPDATE reclamos SET idCausa='24' where idReclamo='"+query.value(0).toString()+"'")){


                    }else{
                        Logs::loguear( "Función: reclamosAlosCualesHayQueAsignarCausaYSintoma == reclamo: "+query.value(0).toString());
                        Logs::loguear(query.lastError().text());

                    }
                }

            }else{
                Logs::loguear( "Función: reclamosAlosCualesHayQueAsignarCausaYSintoma == No hay reclamos sin causa para actualizar ");
            }
        }else{
            Logs::loguear( "Función: reclamosAlosCualesHayQueAsignarCausaYSintoma == SELECT idReclamo ");
            Logs::loguear(query.lastError().text());
        }
    }else{
        Logs::loguear("Función: reclamosAlosCualesHayQueAsignarCausaYSintoma::conexion: No hay conexion disponible");
    }
}

