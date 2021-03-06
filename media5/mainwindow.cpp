#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "classes.h"
#include <database.h>

#define NO_DB

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // DIR for musics and images

    QString sPath = "C:/ ";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);

    // Set buttons checkables
    ui->menu_small_button_album->setCheckable(true);
    ui->menu_small_button_artist->setCheckable(true);
    ui->menu_small_button_list->setCheckable(true);
    ui->menu_small_button_play->setCheckable(true);
    ui->menu_small_button_song->setCheckable(true);

    ui->menu_full_button_album->setCheckable(true);
    ui->menu_full_button_artist->setCheckable(true);
    ui->menu_full_button_list->setCheckable(true);
    ui->menu_full_button_play->setCheckable(true);
    ui->menu_full_button_song->setCheckable(true);

    ui->page_categories_button_select->setCheckable(true);
    ui->page_album_info_button_select->setCheckable(true);
    ui->page_artist_button_select->setCheckable(true);

    ui->player_button_play->setCheckable(true);
    ui->player_button_shuffle->setCheckable(true);

    // Hide tab for add album
    ui->page_add_album_tabs->tabBar()->hide();

#ifdef NO_DB

    Autor *newArtist;
    Musica *newSong;
    Album *newAlbum;
    Playlist *newPlaylist;


    for(int i = 0; i < 5; i++){
        newArtist = new Autor;
        newSong = new Musica;
        newAlbum = new Album;
        newPlaylist = new Playlist;
        QString text;
        QDate date;

        //newArtist
        text = "";
        QTextStream(&text) << "Tromba linda " << i;
        newArtist->setImagem(text);
        text = "";
        QTextStream(&text) << "Eu mesmo " << i;
        newArtist->setNome(text);
        text = "";
        QTextStream(&text) << "PORTUGUESAAAA " << i;
        newArtist->setNacionalidade(text);
        date.setDate(1989,6,24);
        newArtist->setDataNascimento(date);

        //newSong
        text = "";
        QTextStream(&text) << "Musica com este nome " << i;
        newSong->setNome(text);
        text = "";
        QTextStream(&text) << "Está nesta pasta " << i;
        newSong->setDiretoria(text);
        text = "";
        QTextStream(&text) << "Genero da musica " << 5-i;
        newSong->setGenero(text);
        newSong->setFaixa(i);

        //newAlbum
        text = "";
        QTextStream(&text) << "";
        newAlbum->setImagem(text);
        text = "";
        QTextStream(&text) << "Vamos la! " << i;
        newAlbum->setNome(text);
        text = "";
        QTextStream(&text) << "mesmo como eu gosto " << 5-i;
        newAlbum->setGenero(text);
        text = "";
        QTextStream(&text) << "nada a comentar " << i;
        newAlbum->setDescricao(text);

        //newPlaylist

        text = "";
        QTextStream(&text) << "Playlist " << i;
        newPlaylist->setNome(text);
        text = "";
        QTextStream(&text) << "Tem esta e aquela musica " << i;
        newPlaylist->setDescricao(text);

        _albuns.append(newAlbum);
        _playlist.append(newPlaylist);
        _artists.append(newArtist);
        _songs.append(newSong);
    }

    _player.adicionar(&_songs);
    _playlist[2]->setMusicas(&_songs);
    _songs[0]->setAutor(&_artists.mid(1,1));
    _songs[2]->setAutor(&_artists.mid(1,4));
    _songs[4]->setAutor(&_artists.mid(3,2));
    _albuns[1]->adicionar(_songs.value(2));

#endif // NO_DB

    ExpandMenu(false);
    MovePageToAlbuns();
}

MainWindow::~MainWindow()
{
    QMainWindow::centralWidget();

    while (!_albuns.isEmpty())
        _albuns.removeLast();
    while (!_playlist.isEmpty())
        _playlist.removeLast();

    while (!_artists.isEmpty())
        _artists.removeLast();

    while (!_songs.isEmpty())
        _songs.removeLast();

    while (!_newSongList.isEmpty())
        _newSongList.removeLast();

    delete ui;
}

//==============================================================
// Metodos de simplificação
// Para tornar o código mais legivel e de fácil manutenção
QString MainWindow::getArtistsFrom(Album *album)
{
    QString text = "";
    int displayedArtists = 0;
    QList <Musica*> songs;
    album->getMusicas(&songs);

    if(songs.isEmpty()){
        QTextStream(&text) << "Nenhum";
    }else{
        for(int i = 0; i < songs.size(); i++)
        {
            if(displayedArtists == 3)
            {
                break;
            }

            QTextStream(&text) << getArtistsFrom(&displayedArtists,songs[i]);

            if(displayedArtists == 0 && i == songs.size())
            {
                QTextStream(&text) << "Nenhum ";
                break;
            }
        }
    }
    return text;
}

QString MainWindow::getArtistsFrom(Playlist *playlist)
{
    QString text = "";
    int displayedArtists = 0;
    QList <Musica*> songs;
    playlist->getMusicas(&songs);

    if(songs.isEmpty()){
        QTextStream(&text) << "Nenhum";
    }else{
        for(int i = 0; i < songs.size(); i++)
        {
            if(displayedArtists == 3)
            {
                break;
            }

            QTextStream(&text) << getArtistsFrom(&displayedArtists,songs[i]);

            if(displayedArtists == 0 && i == songs.size())
            {
                QTextStream(&text) << "Nenhum ";
                break;
            }
        }
    }
    return text;
}

QString MainWindow::getArtistsFrom(int *displayed, Musica *song)
{
    QString text = "";

    QList <Autor*> artists;
    song->getAutor(&artists);

    if(artists.isEmpty())
        return NULL;
    else{
        for(int i = 0; i < artists.size(); i++){
            if(*displayed != 0)
                QTextStream(&text) << ", ";

            if(*displayed == 3)
            {
                QTextStream(&text) << "...";
                break;
            }
            QTextStream(&text) << artists[i]->getNome();
            *displayed++;
        }
        return text;
    }
}

QList <Album*> MainWindow::getAlbunsFromArtist(Autor *artist)
{
    QList <Album*> albuns;

    for (int i = 0; i < _albuns.size(); i++)
    {
        if(_albuns[i]->hasAutor(artist))
            albuns.append(_albuns[i]);
    }

    return albuns;
}

QList <Musica*> MainWindow::getSongsFromArtist(Autor *artist)
{
    QList <Musica*> songs;

    for (int i = 0; i < _songs.size(); i++)
    {
        if(_songs[i]->hasAutor(artist))
            songs.append(_songs[i]);
    }

    return songs;
}

Album* MainWindow::getAlbumWith(Musica* song)
{
    QList <Musica*> tempList;
    for(int i = 0; i < _albuns.size(); i++)
    {
        tempList.clear();
       _albuns[i]->getMusicas(&tempList);
        if(tempList.contains(song))
            return _albuns[i];
    }
    return NULL;
}

void MainWindow::CheckMenuButton(QString button)
{
    QStringList options;
    /*
     * Albuns   - 0
     * Artists  - 1
     * Player   - 2
     * Playlist - 3
     * Songs    - 4
     * Search   - 5
     * */
    options << "Albuns" << "Artists" << "Player" << "Playlist" << "Songs" << "Search";

    switch(options.indexOf(button))
    {
    case 0:
        //Set album as checked
        ui->menu_small_button_album->setChecked(true);
        ui->menu_full_button_album->setChecked(true);
        ui->menu_small_button_artist->setChecked(false);
        ui->menu_full_button_artist->setChecked(false);
        ui->menu_small_button_list->setChecked(false);
        ui->menu_full_button_list->setChecked(false);
        ui->menu_full_button_play->setChecked(false);
        ui->menu_small_button_play->setChecked(false);
        ui->menu_small_button_song->setChecked(false);
        ui->menu_full_button_song->setChecked(false);

        break;
    case 1:
        //Set artist as checked
        ui->menu_small_button_album->setChecked(false);
        ui->menu_full_button_album->setChecked(false);
        ui->menu_small_button_artist->setChecked(true);
        ui->menu_full_button_artist->setChecked(true);
        ui->menu_small_button_list->setChecked(false);
        ui->menu_full_button_list->setChecked(false);
        ui->menu_full_button_play->setChecked(false);
        ui->menu_small_button_play->setChecked(false);
        ui->menu_small_button_song->setChecked(false);
        ui->menu_full_button_song->setChecked(false);

        break;
    case 2:
        //Set player as checked
        ui->menu_small_button_album->setChecked(false);
        ui->menu_full_button_album->setChecked(false);
        ui->menu_small_button_artist->setChecked(false);
        ui->menu_full_button_artist->setChecked(false);
        ui->menu_small_button_list->setChecked(false);
        ui->menu_full_button_list->setChecked(false);
        ui->menu_full_button_play->setChecked(true);
        ui->menu_small_button_play->setChecked(true);
        ui->menu_small_button_song->setChecked(false);
        ui->menu_full_button_song->setChecked(false);

        break;
    case 3:
        //Set playlist as checked
        ui->menu_small_button_album->setChecked(false);
        ui->menu_full_button_album->setChecked(false);
        ui->menu_small_button_artist->setChecked(false);
        ui->menu_full_button_artist->setChecked(false);
        ui->menu_small_button_list->setChecked(true);
        ui->menu_full_button_list->setChecked(true);
        ui->menu_full_button_play->setChecked(false);
        ui->menu_small_button_play->setChecked(false);
        ui->menu_small_button_song->setChecked(false);
        ui->menu_full_button_song->setChecked(false);

        break;
    case 4:
        //Set Songs as checked
        ui->menu_small_button_album->setChecked(false);
        ui->menu_full_button_album->setChecked(false);
        ui->menu_small_button_artist->setChecked(false);
        ui->menu_full_button_artist->setChecked(false);
        ui->menu_small_button_list->setChecked(false);
        ui->menu_full_button_list->setChecked(false);
        ui->menu_full_button_play->setChecked(false);
        ui->menu_small_button_play->setChecked(false);
        ui->menu_small_button_song->setChecked(true);
        ui->menu_full_button_song->setChecked(true);

        break;
    case 5:
        //Set search as checked
        ui->menu_small_button_album->setChecked(false);
        ui->menu_full_button_album->setChecked(false);
        ui->menu_small_button_artist->setChecked(false);
        ui->menu_full_button_artist->setChecked(false);
        ui->menu_small_button_list->setChecked(false);
        ui->menu_full_button_list->setChecked(false);
        ui->menu_full_button_play->setChecked(false);
        ui->menu_small_button_play->setChecked(false);
        ui->menu_small_button_song->setChecked(false);
        ui->menu_full_button_song->setChecked(false);

        break;
    }
}

void MainWindow::ExpandMenu(bool expand)
{
	if(expand)
	{
		ui->menuTab->setCurrentIndex(0);
    	ui->menuTab->setFixedWidth(200);
	}else{
		ui->menuTab->setCurrentIndex(1);
    	ui->menuTab->setFixedWidth(41);
	}
}

void MainWindow::ShowOptionsTab(bool show)
{
    if(show)
    {
        // Set Options tab
        ui->Player_tab->setCurrentIndex(1);
    }else{
        // Set Player tab
        ui->Player_tab->setCurrentIndex(0);
    }
}

void MainWindow::ShowProgressTab(bool show)
{
    if(show)
    {
        // Set Progress tab
        ui->Player_tab->setCurrentIndex(2);
    }else{
        // Set Player tab
        ui->Player_tab->setCurrentIndex(0);
    }
}

void MainWindow::FormatTableFor(QTableWidget *table, QString format)
{
    QStringList options;
    QStringList tableLabels;
    /*
     * Albuns         - 0
     * Artists        - 1
     * Playlist       - 2
     * Songs          - 3
     * NewSong        - 4
     * SimplifiedSong - 5
     * ArtistName     - 6
     * */
    options << "Albuns" << "Artists" << "Playlist" << "Songs" << "NewSong" << "SimplifiedSong" << "ArtistName";

    switch(options.indexOf(format))
    {
    case 0:
        // Set labels para a tabela de elementos
        tableLabels << tr("Capa") << tr("Nome") << tr("Género") << tr("Artistas");
        table->verticalHeader()->setDefaultSectionSize(50);
        break;

    case 1:
        // Set labels para a tabela de elementos
        tableLabels << tr("Imagem") << tr("Nome") << tr("Nº de Álbuns") << tr("Nº de Musicas");
        table->verticalHeader()->setDefaultSectionSize(50);
        break;

    case 2:
        // Set labels para a tabela de elementos
        tableLabels << tr("Nome") << tr("Tamanho") << tr("Artistas");
        table->verticalHeader()->setDefaultSectionSize(25);
        break;

    case 3:
        // Set labels para a tabela de elementos
        tableLabels << tr("Nome") << tr("Genero") << tr("Album") << tr("Artistas");
        table->verticalHeader()->setDefaultSectionSize(25);
        break;

    case 4:
        // Set labels para a tabela de elementos
        tableLabels << tr("Faixa") << tr("Nome") << tr("Genero") << tr("Diretoria");
        table->verticalHeader()->setDefaultSectionSize(25);
        break;

    case 5:
        // Set labels para a tabela de elementos
        tableLabels << tr("Nome");
        table->verticalHeader()->setDefaultSectionSize(25);
        break;

    case 6:
        // Set labels para a tabela de elementos
        tableLabels << tr("Imagem") << tr("Nome");
        table->verticalHeader()->setDefaultSectionSize(50);
        break;
    }

    table->clear();
    table->setRowCount(0);
    table->setColumnCount(0);
    table->setColumnCount(tableLabels.size());
    table->setHorizontalHeaderLabels(tableLabels);
    table->horizontalHeader()->setHidden(true);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setHidden(true);
    table->setFrameShape(QFrame::NoFrame);
    table->setFrameShadow(QFrame::Sunken);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setTextElideMode(Qt::ElideLeft);
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(false);

}

void MainWindow::AddAlbumLineToTable(QTableWidget *table, Album *album)
{
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    QLabel *artwork;
    table->insertRow(newRow);

    // Artwork
    artwork = new QLabel;
    QPixmap pxmap = QPixmap(album->getImagem());
    if(!pxmap.isNull())
        artwork->setPixmap(QPixmap(album->getImagem()).scaled(50,50));
    else
        artwork->setPixmap(QPixmap(":/music.png"));
    artwork->setAlignment(Qt::AlignCenter);
    artwork->setStyleSheet("background-color: rgba(255, 255, 255, 10);");
    table->setCellWidget(newRow, 0, artwork);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_albuns.indexOf(album));
    item->setData(Qt::DisplayRole,album->getNome());
    table->setItem(newRow, 1, item);

    // Gender
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_albuns.indexOf(album));
    item->setData(Qt::DisplayRole,album->getGenero());
    table->setItem(newRow, 2, item);

    // Artists
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_albuns.indexOf(album));
    item->setData(Qt::DisplayRole,getArtistsFrom(album));
    table->setItem(newRow, 3, item);
}

void MainWindow::AddSongLineToTable(QTableWidget *table, Musica *song)
{
    int newRow = table->rowCount();
    int displayed = 0;
    QTableWidgetItem *item;
    Album *fromAlbum;
    table->insertRow(newRow);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_songs.indexOf(song));
    item->setData(Qt::DisplayRole,song->getNome());
    table->setItem(newRow, 0, item);

    // Gender
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_songs.indexOf(song));
    item->setData(Qt::DisplayRole,song->getGenero());
    table->setItem(newRow, 1, item);

    // Album
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_songs.indexOf(song));
    fromAlbum = getAlbumWith(song);
    item->setData(Qt::DisplayRole,fromAlbum != NULL ? fromAlbum->getNome() : "Nenhum");
    table->setItem(newRow, 2, item);

    // Artist
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_songs.indexOf(song));
    item->setData(Qt::DisplayRole,getArtistsFrom(&displayed, song));
    table->setItem(newRow, 3, item);
}

void MainWindow::AddNewSongLineToTable(QTableWidget *table, Musica *newSong)
{
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    table->insertRow(newRow);

    // Faixa
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_newSongList.indexOf(newSong));
    item->setData(Qt::DisplayRole,newSong->getFaixa());
    table->setItem(newRow, 0, item);

    // Nome
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_newSongList.indexOf(newSong));
    item->setData(Qt::DisplayRole,newSong->getNome());
    table->setItem(newRow, 0, item);

    // Gender
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_newSongList.indexOf(newSong));
    item->setData(Qt::DisplayRole,newSong->getGenero());
    table->setItem(newRow, 1, item);

    // Diretoria
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_newSongList.indexOf(newSong));
    item->setData(Qt::DisplayRole,newSong->getDiretoria());
    table->setItem(newRow, 1, item);
}

void MainWindow::AddSimplifiedSongLineToTable(QTableWidget *table, Musica *song)
{
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    table->insertRow(newRow);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_songs.indexOf(song));
    item->setData(Qt::DisplayRole,song->getNome());
    table->setItem(newRow, 0, item);
}

void MainWindow::AddArtistNameLineToTable(QTableWidget *table, Autor *artist)
{
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    QLabel *photo;
    table->insertRow(newRow);

    // Photo
    photo = new QLabel;
    QPixmap pxmap = QPixmap(artist->getImagem());
    if(!pxmap.isNull())
        photo->setPixmap(QPixmap(artist->getImagem()).scaled(50,50));
    else
        photo->setPixmap(QPixmap(":/social.png"));
    photo->setAlignment(Qt::AlignCenter);
    photo->setStyleSheet("background-color: rgba(255, 255, 255, 10);");
    table->setCellWidget(newRow, 0, photo);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_artists.indexOf(artist));
    item->setData(Qt::DisplayRole,artist->getNome());
    table->setItem(newRow, 1, item);
}

void MainWindow::AddArtistLineToTable(QTableWidget *table, Autor *artist)
{
    QString text;
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    QLabel *photo;
    table->insertRow(newRow);

    // Photo
    photo = new QLabel;
    QPixmap pxmap = QPixmap(artist->getImagem());
    if(!pxmap.isNull())
        photo->setPixmap(QPixmap(artist->getImagem()).scaled(50,50));
    else
        photo->setPixmap(QPixmap(":/social.png"));
    photo->setAlignment(Qt::AlignCenter);
    photo->setStyleSheet("background-color: rgba(255, 255, 255, 10);");
    table->setCellWidget(newRow, 0, photo);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_artists.indexOf(artist));
    item->setData(Qt::DisplayRole,artist->getNome());
    table->setItem(newRow, 1, item);

    // nº Albuns
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_artists.indexOf(artist));
    text = "";
    QTextStream(&text) << getAlbunsFromArtist(artist).size() << " albuns";
    item->setData(Qt::DisplayRole,text);
    table->setItem(newRow, 2, item);

    // nº Songs
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_artists.indexOf(artist));
    text = "";
    QTextStream(&text) << getSongsFromArtist(artist).size() << " musicas";
    item->setData(Qt::DisplayRole,text);
    table->setItem(newRow, 3, item);
}

void MainWindow::AddPlaylistLineToTable(QTableWidget *table, Playlist *playlist)
{
    QString text = "";
    int newRow = table->rowCount();
    QTableWidgetItem *item;
    table->insertRow(newRow);

    // Name
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_playlist.indexOf(playlist));
    item->setData(Qt::DisplayRole,playlist->getNome());
    table->setItem(newRow, 0, item);

    // Size
    item = new QTableWidgetItem;
    QTextStream(&text) << playlist->getSize() << " musicas";
    item->setData(Qt::WhatsThisRole,_playlist.indexOf(playlist));
    item->setData(Qt::DisplayRole,text);
    table->setItem(newRow, 1, item);

    // Artists
    item = new QTableWidgetItem;
    item->setData(Qt::WhatsThisRole,_playlist.indexOf(playlist));
    item->setData(Qt::DisplayRole,getArtistsFrom(playlist));
    table->setItem(newRow, 2, item);
}

void MainWindow::MovePageToAlbuns()
{
    CheckMenuButton("Albuns");

    ui->pages->setCurrentIndex(0);

    Refresh();
}

void MainWindow::MovePageToAlbumInfo(int index)
{
    _showingAlbum = index;
    CheckMenuButton("Albuns");

    ui->pages->setCurrentIndex(1);

    Refresh();
}

void MainWindow::MovePageToArtists()
{
    CheckMenuButton("Artists");

    ui->pages->setCurrentIndex(0);

    Refresh();
}

void MainWindow::MovePageToArtistInfo(int index)
{
    _showingArtist = index;
    CheckMenuButton("Artists");

    ui->pages->setCurrentIndex(5);

    Refresh();
}

void MainWindow::MovePageToPlayer()
{
    CheckMenuButton("Player");

    ui->pages->setCurrentIndex(6);

    Refresh();
}

void MainWindow::MovePageToPlaylists()
{
    CheckMenuButton("Playlist");

    ui->pages->setCurrentIndex(0);

    Refresh();
}

void MainWindow::MovePageToPlaylistInfo(int index)
{
    _showingPlaylist = index;
    CheckMenuButton("Playlist");

    ui->pages->setCurrentIndex(6);

    Refresh();
}

void MainWindow::MovePageToSongs()
{
    CheckMenuButton("Songs");

    ui->pages->setCurrentIndex(0);

    Refresh();
}

void MainWindow::MovePageToSearch()
{
    CheckMenuButton("Search");

    ui->pages->setCurrentIndex(4);

    Refresh();
}

void MainWindow::MovePageToAddAlbuns()
{
	CheckMenuButton("Albuns");

    ui->page_add_album_label_artwork->setPixmap(QPixmap(":/music.png"));
    ui->page_add_album_lineEdit_name->setText("");
    ui->page_add_album_lineEdit_gender->setText("");
    ui->page_add_album_lineEdit_year->setText("");
    _imageURL = "";
    ui->page_add_album_textEdit_description->clear();

    while(!_newSongList.isEmpty())
        _newSongList.removeLast();

    ui->pages->setCurrentIndex(2);
    ui->page_add_album_tabs->setCurrentIndex(0);

    Refresh();
}

void MainWindow::MovePageToAddPlaylist()
{
	CheckMenuButton("Playlist");

    if(_newPlaylist == NULL)
        _newPlaylist = new Playlist;

    ui->pages->setCurrentIndex(7);

    Refresh();
}

void MainWindow::MovePageToAddSongs()
{
	CheckMenuButton("Songs");

    ui->pages->setCurrentIndex(3);

    Refresh();
}

void MainWindow::NewArtist()
{
    mdialog = new Dialog(this);
    Autor *artist;
    mdialog->exec();

    if(mdialog->result() == 1)
    {
        artist = mdialog->getNewArtist();
        artist->setDataAdicao(QDate::currentDate());
        _artists.append(artist);
    }
}

void MainWindow::Refresh()
{
    if(ui->pages->currentIndex() == 0) // categories
    {
        if(ui->menu_small_button_album->isChecked()) // Albuns
        {
            ShowOptionsTab(false);
            ShowProgressTab(false);

            //Reset botão "Selecionar"
            ui->page_categories_button_select->setChecked(false);

            // Order Options
            ui->page_categories_comboBox_order->clear();
            ui->page_categories_comboBox_order->setHidden(false);
            ui->page_categories_comboBox_order->insertItem(0,"Data de Adição");
            ui->page_categories_comboBox_order->insertItem(1,"A a Z");
            ui->page_categories_comboBox_order->insertItem(2,"Género");
            ui->page_categories_comboBox_order->insertItem(3,"Autor");

            //Reset de orderBox
            ui->page_categories_comboBox_order->setCurrentIndex(1);
            ui->page_categories_comboBox_order->setDisabled(false);

            // Set main page Albuns
            ui->page_categories_label_category->setText("Álbuns");

            FormatTableFor(ui->page_categories_tableWidget, "Albuns");
            for(int i = 0; i < _albuns.size(); i++)
            {
                AddAlbumLineToTable(ui->page_categories_tableWidget, _albuns[i]);
            }

        }else if(ui->menu_small_button_artist->isChecked()) // Artists
        {
            ShowOptionsTab(false);
            ShowProgressTab(false);

            //Reset botão "Selecionar"
            ui->page_categories_button_select->setChecked(false);

            // Order Options
            ui->page_categories_comboBox_order->clear();
            ui->page_categories_comboBox_order->setHidden(false);
            ui->page_categories_comboBox_order->insertItem(0,"Data de Adição");
            ui->page_categories_comboBox_order->insertItem(1,"A a Z");

            //Reset de orderBox
            ui->page_categories_comboBox_order->setCurrentIndex(1);
            ui->page_categories_comboBox_order->setDisabled(true);

            // Set main page Autores
            ui->page_categories_label_category->setText("Autores");

            FormatTableFor(ui->page_categories_tableWidget,"Artists");

            //Dados da Tabela
            for (int i = 0; i < _artists.size(); i++)
            {
                AddArtistLineToTable(ui->page_categories_tableWidget,_artists[i]);
            }

        }else if(ui->menu_small_button_list->isChecked()) // Playlists
        {
            ShowOptionsTab(false);
            ShowProgressTab(false);

            //Reset botão "Selecionar"
            ui->page_categories_button_select->setChecked(false);

            // Order Options
            ui->page_categories_comboBox_order->setHidden(true);

            //Reset de orderBox
            ui->page_categories_comboBox_order->setCurrentIndex(1);
            ui->page_categories_comboBox_order->setDisabled(false);

            // Set Main Page Playlists
            ui->page_categories_label_category->setText("Playlists");

            FormatTableFor(ui->page_categories_tableWidget, "Playlist");
            for(int i = 0; i < _playlist.size(); i++)
            {
                AddPlaylistLineToTable(ui->page_categories_tableWidget,_playlist[i]);
            }
        }else if(ui->menu_small_button_song->isChecked()) // Songs
        {
            ShowOptionsTab(false);
            ShowProgressTab(false);

            //Reset botão "Selecionar" e "orderBox"
            ui->page_categories_button_select->setChecked(false);

            // Order Options
            ui->page_categories_comboBox_order->clear();
            ui->page_categories_comboBox_order->setHidden(false);
            ui->page_categories_comboBox_order->insertItem(0,"Data de Adição");
            ui->page_categories_comboBox_order->insertItem(1,"A a Z");
            ui->page_categories_comboBox_order->insertItem(2,"Género");
            ui->page_categories_comboBox_order->insertItem(3,"Autor");
            ui->page_categories_comboBox_order->insertItem(4,"Album");

            //Reset de orderBox
            ui->page_categories_comboBox_order->setCurrentIndex(1);
            ui->page_categories_comboBox_order->setDisabled(false);

            // Set main page Musicas
            ui->page_categories_label_category->setText("Músicas");

            FormatTableFor(ui->page_categories_tableWidget,"Songs");
            // tabela de dados
            for(int i = 0; i < _songs.size(); i++)
            {
                AddSongLineToTable(ui->page_categories_tableWidget,_songs[i]);
            }

        }
    }else if(ui->pages->currentIndex() == 1) // Album Info
    {
        ShowOptionsTab(false);
        ShowProgressTab(false);

        // reset de botão select
        ui->page_album_info_button_select->setChecked(false);

        ui->page_album_info_label_name->setText(_albuns[_showingAlbum]->getNome());
        if(!_albuns[_showingAlbum]->getImagem().isEmpty())
            ui->page_album_info_label_artwork->setPixmap(_albuns[_showingAlbum]->getImagem());
        else
            ui->page_album_info_label_artwork->setPixmap(QString(":/circle-1.png"));
        ui->page_album_info_label_gender->setText(_albuns[_showingAlbum]->getGenero());
        ui->page_album_info_label_year->setText(QString::number(_albuns[_showingAlbum]->getAno()));

        QList <Musica*> songs;
        _albuns[_showingAlbum]->getMusicas(&songs);

        FormatTableFor(ui->page_album_info_tableWidget,"Songs");
        for(int i = 0; i < songs.size(); i++)
        {
            AddSongLineToTable(ui->page_album_info_tableWidget, songs[i]);
        }

    }else if(ui->pages->currentIndex() == 2) // Add Album
    {
        if(ui->page_add_album_tabs->currentIndex() == 0) // Add Album Info
        {
            ShowOptionsTab(false);
            ShowProgressTab(true);

            ui->progress_button_previous->setDisabled(true);
            ui->progress_button_next->setDisabled(false);

        }else if(ui->page_add_album_tabs->currentIndex() == 1) // Add Album Songs
        {
            ShowOptionsTab(false);
            ShowProgressTab(true);

            ui->progress_button_previous->setDisabled(false);
            ui->progress_button_next->setDisabled(false);

            FormatTableFor(ui->page_add_album_tableWidget_toAddMusics,"NewSong");
            ui->page_add_album_tableWidget_toAddMusics->setFrameShape(QFrame::StyledPanel);

            ui->page_add_album_tableWidget_toAddMusics->clear();
            ui->page_add_album_tableWidget_toAddMusics->setRowCount(0);

            // Fill tables
            for(int i = 0; i < _newSongList.size(); i++)
            {
                AddNewSongLineToTable(ui->page_add_album_tableWidget_toAddMusics,_newSongList[i]);
            }

        }else if(ui->page_add_album_tabs->currentIndex() == 2) // Add Album Artists
        {
            ShowOptionsTab(false);
            ShowProgressTab(true);

            ui->progress_button_previous->setDisabled(false);
            ui->progress_button_next->setDisabled(true);

            FormatTableFor(ui->page_add_album_tableWidget_musics,"SimplifiedSong");
            ui->page_add_album_tableWidget_musics->setFrameShape(QFrame::StyledPanel);
            FormatTableFor(ui->page_add_album_tableWidget_artists,"ArtistName");
            ui->page_add_album_tableWidget_artists->setFrameShape(QFrame::StyledPanel);

            ui->page_add_album_tableWidget_artists->clear();
            ui->page_add_album_tableWidget_artists->setRowCount(0);
            ui->page_add_album_tableWidget_musics->clear();
            ui->page_add_album_tableWidget_musics->setRowCount(0);

            QString search = ui->page_add_album_lineEdit_searchArtists->text();

            // Fill tables
            for(int i = 0; i < _artists.size(); i++)
            {
                if(search.isEmpty())
                {
                    AddArtistLineToTable(ui->page_add_album_tableWidget_artists, _artists[i]);

                }else if(_songs[i]->procurar(search))
                {
                    AddArtistLineToTable(ui->page_add_album_tableWidget_artists, _artists[i]);
                }
            }
            for(int i = 0; i < _newSongList.size(); i++)
            {
                AddSimplifiedSongLineToTable(ui->page_add_album_tableWidget_musics,_newSongList[i]);
            }
        }

    }else if(ui->pages->currentIndex() == 3) // Add Song
    {
        ShowOptionsTab(false);
        ShowProgressTab(true);

        ui->progress_button_previous->setDisabled(true);
        ui->progress_button_next->setDisabled(true);

        // Order Options
        ui->page_add_music_comboBox_albuns->clear();
        ui->page_add_music_comboBox_albuns->setHidden(false);
        for(int i = 0; i < _albuns.size(); i++)
        {
            ui->page_add_music_comboBox_albuns->insertItem(i,_albuns[i]->getNome());
        }

        FormatTableFor(ui->page_add_music_tableWidget_artists,"ArtistName");
        ui->page_add_music_tableWidget_artists->setFrameShape(QFrame::StyledPanel);
        for(int i = 0; i < _artists.size(); i++)
        {
            AddArtistNameLineToTable(ui->page_add_music_tableWidget_artists,_artists[i]);
        }
        FormatTableFor(ui->page_add_music_tableWidget_musics,"NewSong");
        ui->page_add_music_tableWidget_musics->setFrameShape(QFrame::StyledPanel);
        for(int i = 0; i < _newSongList.size(); i++)
        {
            AddNewSongLineToTable(ui->page_add_music_tableWidget_musics,_newSongList[i]);
        }

    }else if(ui->pages->currentIndex() == 4) // Search
    {
        ShowOptionsTab(false);
        ShowProgressTab(false);
        QString search = ui->menu_full_lineEdit_search->text();

        FormatTableFor(ui->page_search_tableWidget_albuns,"Albuns");
        ui->page_search_tableWidget_albuns->setFrameShape(QFrame::StyledPanel);
        ui->page_search_tableWidget_albuns->verticalHeader()->setDefaultSectionSize(25);

        FormatTableFor(ui->page_search_tableWidget_artists,"Artists");
        ui->page_search_tableWidget_artists->setFrameShape(QFrame::StyledPanel);
        ui->page_search_tableWidget_artists->verticalHeader()->setDefaultSectionSize(25);

        FormatTableFor(ui->page_search_tableWidget_musics,"Songs");
        ui->page_search_tableWidget_musics->setFrameShape(QFrame::StyledPanel);

        for(int i = 0; i < _songs.size(); i++)
        {
            if(search.isEmpty())
            {
                AddSongLineToTable(ui->page_search_tableWidget_musics, _songs[i]);

            }else{
                if(_songs[i]->procurar(search))
                    AddSongLineToTable(ui->page_search_tableWidget_musics, _songs[i]);
            }
        }
        for(int i = 0; i < _artists.size(); i++)
        {
            if(search.isEmpty())
            {
                AddArtistLineToTable(ui->page_search_tableWidget_artists, _artists[i]);

            }else{
                if(_artists[i]->procurar(search))
                    AddArtistLineToTable(ui->page_search_tableWidget_artists, _artists[i]);
            }
        }
        for(int i = 0; i < _albuns.size(); i++)
        {
            if(search.isEmpty())
            {
                AddAlbumLineToTable(ui->page_search_tableWidget_albuns, _albuns[i]);

            }else{
                if(_albuns[i]->procurar(search))
                    AddAlbumLineToTable(ui->page_search_tableWidget_albuns, _albuns[i]);
            }
        }

    }else if(ui->pages->currentIndex() == 5) // Artist
    {
        ShowOptionsTab(false);
        ShowProgressTab(false);

        //Reset botão "Selecionar"
        ui->page_artist_button_select->setChecked(false);

        ui->page_artist_label_name->setText(_artists[_showingArtist]->getNome());

        QList <Album*> albuns = getAlbunsFromArtist(_artists[_showingArtist]);

        FormatTableFor(ui->page_artist_tableWidget_albuns,"Albuns");
        for(int i = 0; i < albuns.size(); i++)
        {
            AddAlbumLineToTable(ui->page_artist_tableWidget_albuns,albuns[i]);
        }
    }else if(ui->pages->currentIndex() == 6) // Playlist
    {
        if(ui->menu_small_button_play->isChecked()) // Player
        {
            ShowOptionsTab(false);
            ShowProgressTab(false);

            ui->page_playlist_label_name->setText("Em Execução");
            ui->page_playlist_button_play->setHidden(true);

            QList <Musica*> songs;
            _player.getMusicas(&songs);

            FormatTableFor(ui->page_playlist_tableWidget,"Songs");
            for (int i = 0; i < songs.size(); i++)
            {
                AddSongLineToTable(ui->page_playlist_tableWidget,songs[i]);
            }

        }else{ // Playlist
            ShowOptionsTab(false);
            ShowProgressTab(false);

            ui->page_playlist_label_name->setText(_playlist[_showingPlaylist]->getNome());
            ui->page_playlist_button_play->setHidden(false);

            FormatTableFor(ui->page_playlist_tableWidget,"Songs");
            QList <Musica*> songs;
            _playlist[_showingPlaylist]->getMusicas(&songs);

            for (int i = 0; i < songs.size(); i++)
            {
                AddSongLineToTable(ui->page_playlist_tableWidget,songs[i]);
            }

        }
    }else if(ui->pages->currentIndex() == 7) // Add Playlist
    {
        ShowOptionsTab(false);
        ShowProgressTab(true);

        ui->progress_button_previous->setDisabled(true);
        ui->progress_button_next->setDisabled(true);

        FormatTableFor(ui->page_add_playlist_tableWidget_toAdd,"SimplifiedSong");
        ui->page_add_playlist_tableWidget_toAdd->setFrameShape(QFrame::StyledPanel);
        FormatTableFor(ui->page_add_playlist_tableWidget_Added,"SimplifiedSong");
        ui->page_add_playlist_tableWidget_Added->setFrameShape(QFrame::StyledPanel);

        QString search = ui->page_add_playlist_lineEdit_search->text();

        for(int i = 0; i < _songs.size(); i++)
        {
            if(search.isEmpty())
            {
                AddSimplifiedSongLineToTable(ui->page_add_playlist_tableWidget_toAdd, _songs[i]);

            }else if(_songs[i]->procurar(search))
            {
                AddSimplifiedSongLineToTable(ui->page_add_playlist_tableWidget_toAdd, _songs[i]);
            }
        }

        _newSongList.clear();
        _newPlaylist->getMusicas(&_newSongList);
        for(int i = 0; i < _newSongList.size(); i++)
        {
            AddSimplifiedSongLineToTable(ui->page_add_playlist_tableWidget_Added, _newSongList[i]);
        }
    }
}

//==============================================================
// Handlers para ações de utilizador (Menu)
void MainWindow::on_menu_small_button_search_clicked()
{
    ExpandMenu(true);

    MovePageToSearch();
}

void MainWindow::on_menu_small_button_album_clicked()
{
    MovePageToAlbuns();
}

void MainWindow::on_menu_small_button_artist_clicked()
{
    MovePageToArtists();
}

void MainWindow::on_menu_small_button_list_clicked()
{
    MovePageToPlaylists();
}

void MainWindow::on_menu_small_button_menu_clicked()
{
    ExpandMenu(true);
}

void MainWindow::on_menu_small_button_play_clicked()
{
    MovePageToPlayer();
}

void MainWindow::on_menu_small_button_song_clicked()
{
    MovePageToSongs();
}

void MainWindow::on_menu_full_button_add_album_clicked()
{
    MovePageToAddAlbuns();
}

void MainWindow::on_menu_full_button_add_artist_clicked()
{
    NewArtist();
}

void MainWindow::on_menu_full_button_add_list_clicked()
{
    MovePageToAddPlaylist();
}

void MainWindow::on_menu_full_button_add_song_clicked()
{
    MovePageToAddSongs();
}

void MainWindow::on_menu_full_button_album_clicked()
{
    MovePageToAlbuns();
}

void MainWindow::on_menu_full_button_artist_clicked()
{
    MovePageToArtists();
}

void MainWindow::on_menu_full_button_list_clicked()
{
    MovePageToPlaylists();
}

void MainWindow::on_menu_full_button_menu_clicked()
{
    ExpandMenu(false);
}

void MainWindow::on_menu_full_button_play_clicked()
{
    MovePageToPlayer();
}

void MainWindow::on_menu_full_button_search_clicked()
{
    MovePageToSearch();
}

void MainWindow::on_menu_full_button_song_clicked()
{
    MovePageToSongs();
}

void MainWindow::on_menu_full_lineEdit_search_returnPressed()
{
    Refresh();
}

//==============================================================
// Handlers para ações de utilizador (Page_Categories)
void MainWindow::on_page_categories_button_add_clicked()
{
    if(ui->menu_small_button_album->isChecked() || ui->menu_full_button_album->isChecked())
        {
            MovePageToAddAlbuns();
        }

        if(ui->menu_small_button_artist->isChecked() || ui->menu_full_button_artist->isChecked())
        {
            NewArtist();
        }

        if( ui->menu_small_button_song->isChecked() ||  ui->menu_full_button_song->isChecked())
        {
             MovePageToAddSongs();
        }

        if( ui->menu_small_button_list->isChecked() || ui->menu_full_button_list->isChecked())
        {
             MovePageToAddPlaylist();
        }
}

void MainWindow::on_page_categories_button_select_toggled(bool checked)
{
    if(checked)
    {
        ShowOptionsTab(true);
        ui->page_categories_tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    }else{
        ShowOptionsTab(false);
        ui->page_categories_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void MainWindow::on_page_categories_button_random_clicked()
{
    if(ui->menu_small_button_album->isChecked())
    {
        _player.parar();
        _player.removerTodas();

        QList <Musica*> newList;
        _albuns[rand() % ui->page_categories_tableWidget->rowCount()]->getMusicas(&newList);

        _player.adicionar(&newList);
        if(!ui->player_button_shuffle->isChecked())
            ui->player_button_shuffle->setChecked(true);
        _player.play();
        MovePageToPlayer();

    }else if(ui->menu_small_button_song->isChecked())
    {
        _player.parar();
        _player.removerTodas();

        _player.adicionar(&_songs);
        if(!ui->player_button_shuffle->isChecked())
            ui->player_button_shuffle->setChecked(true);
        _player.play();
        MovePageToPlayer();

    }else if(ui->menu_small_button_artist->isChecked())
    {
        _player.parar();
        _player.removerTodas();

        QList <Musica*> newList;
        newList = getSongsFromArtist(_artists[rand() % ui->page_categories_tableWidget->rowCount()]);

        _player.adicionar(&newList);
        if(!ui->player_button_shuffle->isChecked())
            ui->player_button_shuffle->setChecked(true);
        _player.play();
        MovePageToPlayer();

    }else if(ui->menu_small_button_list->isChecked())
    {
        _player.parar();
        _player.removerTodas();

        QList <Musica*> newList;
        _playlist[rand() % ui->page_categories_tableWidget->rowCount()]->getMusicas(&newList);

        _player.adicionar(&newList);
        if(!ui->player_button_shuffle->isChecked())
            ui->player_button_shuffle->setChecked(true);
        _player.play();
        MovePageToPlayer();
    }
}

void MainWindow::on_page_categories_comboBox_order_currentIndexChanged(int index)
{
    if(ui->menu_small_button_album->isChecked())
    {
        switch(index)
        {
        case 0:
            // data de adição (ainda não faz nada)
            break;
        case 1:
            // A a Z
            ui->page_categories_tableWidget->sortByColumn(1, Qt::AscendingOrder);
            break;
        case 2:
            // Genero
            ui->page_categories_tableWidget->sortByColumn(2, Qt::AscendingOrder);
            break;
        case 3:
            // Autor
            ui->page_categories_tableWidget->sortByColumn(3, Qt::AscendingOrder);
            break;
        }
    }else if(ui->menu_small_button_song->isChecked())
    {
        switch(index)
        {
        case 0:
            // data de adição (ainda não faz nada)
            break;
        case 1:
            // A a Z
            ui->page_categories_tableWidget->sortByColumn(0, Qt::AscendingOrder);
            break;
        case 2:
            // Genero
            ui->page_categories_tableWidget->sortByColumn(1, Qt::AscendingOrder);
            break;
        case 3:
            // Autor
            ui->page_categories_tableWidget->sortByColumn(3, Qt::AscendingOrder);
            break;
        case 4:
            // Album
            ui->page_categories_tableWidget->sortByColumn(2, Qt::AscendingOrder);
            break;
        }
    }
}

void MainWindow::on_page_categories_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (ui->menu_full_button_album->isChecked()){
        MovePageToAlbumInfo(index.data(Qt::WhatsThisRole).toInt());
    }else if (ui->menu_full_button_artist->isChecked()){
        MovePageToArtistInfo(index.data(Qt::WhatsThisRole).toInt());
    }else if (ui->menu_full_button_list->isChecked()){
        MovePageToPlaylistInfo(index.data(Qt::WhatsThisRole).toInt());
    }else if (ui->menu_full_button_song->isChecked()){
        _player.removerTodas();
        _player.adicionar(_songs[index.data(Qt::WhatsThisRole).toInt()]);
        ui->player_button_shuffle->setChecked(false);
        _player.play();
    }
}

//==============================================================
// Handlers para ações de utilizador (Page Album Info)

void MainWindow::on_page_album_info_button_play_clicked()
{
    _player.parar();
    _player.removerTodas();

    QList <Musica*> newList;
    int musicToAdd;

    for(int i = 0; i < ui->page_album_info_tableWidget->rowCount(); i++)
    {
        musicToAdd = ui->page_album_info_tableWidget->item(i,0)->data(Qt::WhatsThisRole).toInt();
        newList.append(_songs[musicToAdd]);
    }

    _player.adicionar(&newList);
//    if(ui->player_button_shuffle->isChecked())
//        ui->player_button_shuffle->setChecked(false);
    _player.play();
    MovePageToPlayer();
}

//==============================================================
//==============================================================
//==============================================================
//                POINT OF NOT DONE YET
//==============================================================
//==============================================================
//==============================================================
void MainWindow::on_page_album_info_button_addTo_clicked()
{

}

void MainWindow::on_page_album_info_button_remove_clicked()
{

}

void MainWindow::on_page_album_info_button_exploreArtist_clicked()
{
    int songIndex = ui->page_categories_tableWidget->selectedItems().first()->data(Qt::WhatsThisRole).toInt();
    QList <Autor*> artists;

    _songs[songIndex]->getAutor(&artists);

    if(artists.size() == 1)
        MovePageToArtistInfo(_artists.indexOf(artists.first()));

}

void MainWindow::on_page_album_info_button_select_toggled(bool checked)
{
    if(checked)
    {
        ShowOptionsTab(true);
        ui->page_album_info_tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    }else{
        ShowOptionsTab(false);
        ui->page_album_info_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void MainWindow::on_page_album_info_tableWidget_doubleClicked(const QModelIndex &index)
{
    _player.removerTodas();
    _player.adicionar(_songs[index.data(Qt::WhatsThisRole).toInt()]);
    if(ui->player_button_shuffle->isChecked())
        ui->player_button_shuffle->setChecked(false);
    _player.play();
}

//==============================================================
// Handlers para ações de utilizador (Page Add Album)

void MainWindow::on_page_add_album_button_addArtwork_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open a File"),"","Image files (*.jpg , *.png)");

    if(!filename.isEmpty())
    {
        _imageURL = filename;
        ui->page_add_album_label_artwork->setPixmap(QPixmap(filename));
    }

    Refresh();
}

void MainWindow::on_page_add_album_button_addMusic_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this,tr("Open a File"),"","MP3 files (*.mp3)");

    if(!filename.isNull())
    {
        Musica *newSong;

        newSong = new Musica;
        newSong->setDiretoria(filename);
        newSong->retrieveInfo(newSong->getDiretoria());
        _newSongList.append(newSong);

    }

    Refresh();
}

void MainWindow::on_page_add_album_button_addFolder_clicked()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    QDir dir(folderName);
    QStringList filters;
    filters << "*.mp3";
    QStringList filenames = dir.entryList(filters,QDir::Files,QDir::Name);

    Musica *newSong;
    for(int i = 0; i < filenames.size(); i++)
    {
        if(!filenames[i].isEmpty())
        {
            newSong = new Musica;
            newSong->setDiretoria(folderName + "/" + filenames[i]);
            newSong->retrieveInfo(newSong->getDiretoria());
            _newSongList.append(newSong);
        }
    }

    Refresh();
}

void MainWindow::on_page_add_album_button_remove_clicked()
{
    int rowToRemove, indexToRemove;
    rowToRemove = ui->page_add_album_tableWidget_toAddMusics->selectedItems().first()->row();
    indexToRemove = ui->page_add_album_tableWidget_toAddMusics->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    _newSongList.removeAt(indexToRemove);

    Refresh();
}

void MainWindow::on_page_add_album_button_addArtistTo_clicked()
{
    int artistIndex = ui->page_add_album_tableWidget_artists->selectedItems().first()->data(Qt::WhatsThisRole).toInt();
    int songIndex = ui->page_add_album_tableWidget_musics->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    _newSongList[songIndex]->addAutor(_artists[artistIndex]);

    Refresh();
}

void MainWindow::on_page_add_album_button_addArtistToAll_clicked()
{
    int artistIndex = ui->page_add_album_tableWidget_artists->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    for(int i = 0; i < _newSongList.size(); i++)
    {
        _newSongList[i]->addAutor(_artists[artistIndex]);
    }

    Refresh();
}

void MainWindow::on_page_add_album_button_removeArtistFrom_clicked()
{
    int artistIndex = ui->page_add_album_tableWidget_artists->selectedItems().first()->data(Qt::WhatsThisRole).toInt();
    int songIndex = ui->page_add_album_tableWidget_musics->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    if(_newSongList[songIndex]->hasAutor(_artists[artistIndex]))
    {
        _newSongList[songIndex]->removeAutor(_artists[artistIndex]);
    }

    Refresh();
}

void MainWindow::on_page_add_album_button_newArtist_clicked()
{
    NewArtist();

    Refresh();
}

void MainWindow::on_page_add_album_lineEdit_searchArtists_returnPressed()
{
    Refresh();
}

void MainWindow::on_page_add_album_lineEdit_searchArtists_textChanged(const QString &arg1)
{
    Refresh();
}

//==============================================================
// Handlers para ações de utilizador (Page Add Music)

void MainWindow::on_page_add_music_button_addFolder_clicked()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    QDir dir(folderName);
    QStringList filters;
    filters << "*.mp3";
    QStringList filenames = dir.entryList(filters,QDir::Files,QDir::Name);

    Musica *newSong;
    for(int i = 0; i < filenames.size(); i++)
    {
        if(!filenames[i].isEmpty())
        {
            newSong = new Musica;
            newSong->setDiretoria(folderName + "/" + filenames[i]);
            newSong->retrieveInfo(newSong->getDiretoria());
            _newSongList.append(newSong);
        }
    }

    Refresh();
}

void MainWindow::on_page_add_music_button_addMusic_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open a File"),"","MP3 files (*.mp3)");

    if(!filename.isEmpty())
    {
        Musica *newSong;

        newSong = new Musica;
        newSong->setDiretoria(filename);
        newSong->retrieveInfo(newSong->getDiretoria());
        _newSongList.append(newSong);
    }

    Refresh();
}

void MainWindow::on_page_add_music_comboBox_albuns_currentIndexChanged(int index)
{
    ui->page_add_music_comboBox_albuns->setCurrentIndex(index);
}

//==============================================================
// Handlers para ações de utilizador (Page Search)
void MainWindow::on_page_search_tableWidget_artists_doubleClicked(const QModelIndex &index)
{
    MovePageToArtistInfo(index.data(Qt::WhatsThisRole).toInt());
}

void MainWindow::on_page_search_tableWidget_albuns_doubleClicked(const QModelIndex &index)
{
    MovePageToAlbumInfo(index.data(Qt::WhatsThisRole).toInt());
}

void MainWindow::on_page_search_tableWidget_musics_doubleClicked(const QModelIndex &index)
{
    _player.removerTodas();
    _player.adicionar(_songs[index.data(Qt::WhatsThisRole).toInt()]);
    if(ui->player_button_shuffle->isChecked())
        ui->player_button_shuffle->setChecked(false);
    _player.play();
}

//==============================================================
// Handlers para ações de utilizador (Page Artist)

void MainWindow::on_page_artist_button_play_clicked()
{
    _player.parar();
    _player.removerTodas();

    QList <Musica*> newList;

    for(int i = 0; i < _songs.size(); i++)
    {
        if(_songs[i]->hasAutor(_artists[_showingArtist]))
            newList.append(_songs[i]);
    }

    _player.adicionar(&newList);
    if(ui->player_button_shuffle->isChecked())
        ui->player_button_shuffle->setChecked(false);
    _player.play();
}

void MainWindow::on_page_artist_button_addTo_clicked()
{

}

void MainWindow::on_page_artist_button_remove_clicked()
{

}

void MainWindow::on_page_artist_button_select_toggled(bool checked)
{
    if(checked)
    {
        ShowOptionsTab(true);
        ui->page_artist_tableWidget_albuns->setSelectionMode(QAbstractItemView::MultiSelection);
    }else{
        ShowOptionsTab(false);
        ui->page_artist_tableWidget_albuns->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void MainWindow::on_page_artist_tableWidget_albuns_doubleClicked(const QModelIndex &index)
{
    MovePageToAlbumInfo(index.data(Qt::WhatsThisRole).toInt());
}

//==============================================================
// Handlers para ações de utilizador (Page Playlist)

void MainWindow::on_page_playlist_button_play_clicked()
{
    _player.parar();
    _player.removerTodas();

    QList <Musica*> newList;
    int musicToAdd;

    for(int i = 0; i < ui->page_playlist_tableWidget->rowCount(); i++)
    {
        musicToAdd = ui->page_playlist_tableWidget->item(i,0)->data(Qt::WhatsThisRole).toInt();
        newList.append(_songs[musicToAdd]);
    }

    _player.adicionar(&newList);
    if(ui->player_button_shuffle->isChecked())
        ui->player_button_shuffle->setChecked(false);
    _player.play();
}

void MainWindow::on_page_playlist_button_addMusic_clicked()
{

}

void MainWindow::on_page_playlist_button_remove_clicked()
{

}

void MainWindow::on_page_playlist_tableWidget_doubleClicked(const QModelIndex &index)
{
    if(!ui->page_playlist_button_play->isVisible())
    {
        _player.removerTodas();
        _player.adicionar(_songs[index.data(Qt::WhatsThisRole).toInt()]);
        if(ui->player_button_shuffle->isChecked())
            ui->player_button_shuffle->setChecked(false);
        _player.play();
    }
}

//==============================================================
// Handlers para ações de utilizador (Page Add Playlist)

void MainWindow::on_page_add_playlist_button_search_clicked()
{
    Refresh();
}

void MainWindow::on_page_add_playlist_button_add_clicked()
{
    int toAddIndex = ui->page_add_playlist_tableWidget_toAdd->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    _newPlaylist->adicionar(_songs[toAddIndex]);

    Refresh();
}

void MainWindow::on_page_add_playlist_button_remove_clicked()
{
    int toRemoveIndex = ui->page_add_playlist_tableWidget_Added->selectedItems().first()->data(Qt::WhatsThisRole).toInt();

    _newPlaylist->remover(_songs[toRemoveIndex]);

    Refresh();
}

void MainWindow::on_page_add_playlist_lineEdit_search_returnPressed()
{
    Refresh();
}

void MainWindow::on_page_add_playlist_lineEdit_search_textChanged(const QString &arg1)
{
    Refresh();
}

//==============================================================
// Handlers para ações de utilizador (Tab Player)

void MainWindow::on_player_slider_sliderReleased()
{

}

void MainWindow::on_player_button_previous_clicked()
{

}

void MainWindow::on_player_button_play_clicked()
{

}

void MainWindow::on_player_button_stop_clicked()
{

}

void MainWindow::on_player_button_next_clicked()
{

}

void MainWindow::on_player_button_shuffle_toggled(bool checked)
{
    _player.aleatorio(checked);
}

//==============================================================
// Handlers para ações de utilizador (Tab Progress)

void MainWindow::on_progress_button_previous_clicked()
{
    if(ui->page_add_album_tabs->currentIndex() != 0)
    {
        ui->page_add_album_tabs->setCurrentIndex(ui->page_add_album_tabs->currentIndex()-1);

        Refresh();
    }
}

void MainWindow::on_progress_button_next_clicked()
{
    if(ui->page_add_album_tabs->currentIndex() != 2)
    {
        ui->page_add_album_tabs->setCurrentIndex(ui->page_add_album_tabs->currentIndex()+1);

        Refresh();
    }
}

void MainWindow::on_progress_button_cancel_clicked()
{
    if(ui->menu_small_button_album->isChecked())
    {
        MovePageToAlbuns();
        while (!_newSongList.isEmpty())
            _newSongList.removeLast();

    }else if(ui->menu_small_button_song->isChecked())
    {
        MovePageToSongs();
        while (!_newSongList.isEmpty())
            _newSongList.removeLast();

    }else if(ui->menu_small_button_list->isChecked())
    {
        MovePageToPlaylists();
        delete _newPlaylist;
    }
}

void MainWindow::on_progress_button_save_clicked()
{
    if(ui->menu_small_button_album->isChecked())
    {
        if(ui->page_add_album_lineEdit_name->text() == NULL ||
                ui->page_add_album_lineEdit_gender->text() == NULL)
        {
         /*
         * Avisos de irregularidades ao criar album ou assim
         * */
        }else{
            // Tudo certo para criar album

            Album *newAlbum;
            newAlbum = new Album;

            newAlbum->setNome(ui->page_add_album_lineEdit_name->text());
            newAlbum->setGenero(ui->page_add_album_lineEdit_gender->text());
            newAlbum->setAno(ui->page_add_album_lineEdit_year->text().toInt());
            newAlbum->setImagem(_imageURL);
            newAlbum->setDescricao(ui->page_add_album_textEdit_description->toPlainText());

            newAlbum->criar(QDir::currentPath() +"/debug/album/ID_"+ QString::number(newAlbum->getIdBD()) + newAlbum->getNome());

            for (int i = 0; i < _newSongList.size(); i++)
            {
                _newSongList[i]->criar(newAlbum->getDiretoria());
                newAlbum->adicionar(_newSongList[i]);
                _songs.append(_newSongList[i]);
            }

            _albuns.append(newAlbum);

            MovePageToAlbuns();

        }
    }else if(ui->menu_small_button_song->isChecked())
    {
        int albumIndex = ui->page_add_music_comboBox_albuns->currentIndex();

        for (int i = 0; i < _newSongList.size(); i++)
        {
            _newSongList[i]->criar(_albuns[albumIndex]->getDiretoria());
            _albuns[albumIndex]->adicionar(_newSongList[i]);
            _songs.append(_newSongList[i]);
        }

        MovePageToSongs();
    }else if(ui->menu_small_button_list->isChecked())
    {
        _newPlaylist->setNome(ui->page_add_playlist_lineEdit_name->text());
        _newPlaylist->setDescricao(ui->page_add_playlist_plainText_description->toPlainText());
        _newPlaylist->setDataAdicao(QDate::currentDate());
        _playlist.append(_newPlaylist);
        MovePageToPlaylists();
    }
}

//==============================================================
// Handlers para ações de utilizador (Tab Options)

void MainWindow::on_options_button_play_clicked()
{

}

void MainWindow::on_options_button_edit_clicked()
{

}

void MainWindow::on_options_button_remove_clicked()
{

}

void MainWindow::on_options_button_information_clicked()
{

}
