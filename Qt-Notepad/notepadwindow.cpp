#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //Establecemos el tamaño inicial de la ventana
        this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
        this->setWindowTitle(tr("Super editor de texto"));

    //Inicializamos los menus
    mainMenu_= new QMenuBar(this);
    toolMenu_= new  QToolBar(this);

    //Archivo
    mnuArchivo_ = new QMenu (tr("&Archivo"), this);//Especificamos el texto del menu
    mainMenu_-> addMenu(mnuArchivo_);

    //Editar
    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    //Formato
    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    //Ayuda
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);


    //acciones
    //abrir
    actArchivoAbrir_ = new QAction(QIcon(":/new/prefix1/edit-find.png"),tr("&Abrir"),this);
    actArchivoAbrir_-> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    mnuArchivo_->addAction(actArchivoAbrir_);
    toolMenu_->addAction(actArchivoAbrir_);
    //guardar
    actArchivoGuardar_ = new QAction(tr("&Guardar"),this);
    actArchivoGuardar_-> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);
    toolMenu_->addAction(actArchivoGuardar_);
    //Cerrar
    actArchivoCerrar_= new QAction(tr("&Cerrar"),this);
    actArchivoCerrar_->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q));
    mnuArchivo_->addAction(actArchivoCerrar_);
    toolMenu_->addAction(actArchivoCerrar_);

    //Copiar
    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);
    toolMenu_->addAction(actEditarCopiar_);
    //Cortar
    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);
    toolMenu_->addAction(actEditarCortar_);
    //Pegar
    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);
    toolMenu_->addAction(actEditarPegar_);

    //deshacer
    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarDeshacer_);
     toolMenu_->addAction(actEditarDeshacer_);

    //Rehacer
    actEditarRehacer_ = new QAction(tr("&Reshacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarRehacer_);
    toolMenu_->addAction(actEditarRehacer_);


    //Fuente
    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);
    toolMenu_->addAction(actFormatoFuente_);

    //Acercade

    actAyudaAcerca_=new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcerca_);


   //Colocacion de elementos
   //le decimos donde colocarse la barra del menu y la de herramientas
    setMenuBar(mainMenu_);
    addToolBar(toolMenu_);
   //colamos la ventana de texto
    txtEditor_ = new QPlainTextEdit(this);
    setCentralWidget(txtEditor_);//Centramos el widget


    //Conectamos las aciones de los menus con nuestros slots
    connect(actArchivoAbrir_, SIGNAL(triggered()),this, SLOT (alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()),this, SLOT (alGuardar()));
    connect(actArchivoCerrar_, SIGNAL(triggered()),this, SLOT (close()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));
    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT (acerca()));


}
NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
      mainMenu_->deleteLater();
      actArchivoAbrir_->deleteLater();
      actArchivoGuardar_->deleteLater();
      mnuArchivo_->deleteLater();
      actEditarCopiar_->deleteLater();
      actEditarPegar_->deleteLater();
      mnuEditar_->deleteLater();
      actFormatoFuente_->deleteLater();
      mnuFormato_->deleteLater();
      txtEditor_->deleteLater();

}

void NotepadWindow:: alAbrir(){
//mostramos dialogo de apertura de fichero
    QString nombreArchivo;
    nombreArchivo = QFileDialog:: getOpenFileName(this,tr("Abrir archivo plano de texto"),"",tr("Archivo de texto plano (*.txt)"));
    if (nombreArchivo != ""){
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)){
            //Solo permiso de lectura
            txtEditor_->setPlainText(archivo.readAll());
            //Cerramos el fichero
            archivo.close();
        }
    }
}

void NotepadWindow:: alGuardar(){
    QString nombreArchivo;
    nombreArchivo = QFileDialog:: getSaveFileName(this,tr("Guardar archivo"),"",tr("Archivo de texto plano (*.txt)"));
    if (nombreArchivo != ""){
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly|QFile::Truncate)){
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}

void NotepadWindow::acerca()
{
    QMessageBox::about(this,"Acerca de","Este es un editor de texto");
}
