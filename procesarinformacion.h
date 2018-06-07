#ifndef PROCESARINFORMACION_H
#define PROCESARINFORMACION_H

#include <QString>

class ProcesarInformacion
{
public:

    static bool leerDatosDBOrigenReclamos();
    static bool leerDatosDBOrigenTareas();
    static bool leerDatosDBOrigenConceptos();

    static bool grabarDatosDBDestino(QString);

    static bool cargoDatosReclamosTiempos();


    static bool eliminarDatosDBDestino();
    static bool eliminarDatosTemporalesDBOrigen();
    static bool borrarTablasDBOrigen();

    static bool crearTablasTemporales();
    static void setearConsultasSql();
    static bool prepararReclamosParaCalcularTiempos();

    static bool guardaTiempoEnEstadoNuevo(QString , QString);
    static bool guardaTiempoEnEstadoAsignado(QString ,QString);
    static bool guardaTiempoEnEstadoEsperaRespuestaCliente(QString ,QString);
    static bool guardaTiempoEnEstadoEsperaRespuestaClienteHorarioSisteco(QString ,QString);
    static bool guardaTiempoEnEstadoEsperaRespuestaObjetos(QString ,QString);
    static bool guardaTiempoTareaEnReclamo(QString);
    static bool guardaTiempoTotalDeReclamo(QString ,QString);

    static bool esUnDiaFeriadoFijo(QString );

    static QString retornaTipoReclamo(QString );

    static bool retornaSiEsReclamoCoordinado(QString);
    static QString retornaReclamoDondeEmpezarABorrar(QString, int );



    static bool actualizarReclamoTiempoEstadoNuevo(QString , qlonglong );
    static bool actualizarReclamoTiempoEstadoAsignado(QString , qlonglong );
    static bool actualizarReclamoTiempoEstadoEsperaRespuestaCliente(QString , qlonglong );    
    static bool actualizarReclamoTiempoEstadoEsperaRespuestaClienteHorarioSisteco(QString , qlonglong );
    static bool actualizarReclamoTiempoEstadoEsperaObjetos(QString ,qlonglong );
    static bool actualizarReclamoTiempoTareas(QString ,qlonglong );
    static bool actualizarReclamoTiempoTotalDeReclamo(QString ,qlonglong );

    static void recavarReclamosQueNoSeCargan();

    static void reclamosAlosCualesHayQueAsignarCausaYSintoma();


    static int EjectuarComando(QString);

    static void informeDeCargaDeDatosAlmacen(QString);




    static QString getConsultaSqlRemotaReclamos(){
        return consultaSqlRemotaReclamos;
    }
    static QString getConsultaSqlRemotaTareas(){
        return consultaSqlRemotaTareas;
    }
    static QString getConsultaSqlRemotaConceptos(){
        return consultaSqlRemotaConceptos;
    }
    static QString getReclamoDesdeDondeEmpezarABorrar(){
        return reclamoDesdeDondeEmpezarABorrar;
    }



private:
    ProcesarInformacion();
    static QString consultaSqlRemotaReclamos;
    static QString consultaSqlRemotaTareas;
    static QString consultaSqlRemotaConceptos;

    static QString reclamoDesdeDondeEmpezarABorrar;

    static void setConsultaSqlRemotaReclamos(QString value){
        consultaSqlRemotaReclamos=value;
    }

    static void setConsultaSqlRemotaTareas(QString value){
        consultaSqlRemotaTareas=value;
    }

    static void setConsultaSqlRemotaConceptos(QString value){
        consultaSqlRemotaConceptos=value;
    }

    static void setReclamoDesdeDondeEmpezarABorrar(QString value){
        reclamoDesdeDondeEmpezarABorrar=value;
    }

};

#endif // PROCESARINFORMACION_H
