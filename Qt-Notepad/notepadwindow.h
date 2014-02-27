#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
#include <QMessageBox>
#include <QToolBar>
#include <QFont>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alFuenteNegrita();
    void alFuenteCursiva();
    void alFuenteSubrayado();
    void acerca();

   private:
       QMenuBar* mainMenu_;
       QToolBar* toolMenu_;
       QMenu* mnuArchivo_;
       QAction* actArchivoAbrir_;
       QAction* actArchivoGuardar_;
       QAction* actArchivoCerrar_;
       QMenu* mnuFormato_;
       QAction* actFormatoFuente_;
       QMenu* mnuEditar_;
       QAction* actEditarCopiar_;
       QAction* actEditarCortar_;
       QAction* actEditarPegar_;
       QAction* actEditarDeshacer_;
       QAction* actEditarRehacer_;
       QAction* actFormatoNegrita_;
       QAction* actFormatoCursiva_;
       QAction* actFormatoSubrayado_;
       QMenu* mnuAyuda_;
       QAction* actAyudaAcerca_;
       QTextEdit* txtEditor_;
       QClipboard * portapapeles_;
};

#endif // NOTEPADWINDOW_H
