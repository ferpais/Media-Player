/**
 * @file database.h
 *
 * @author Tudo e Todos
 * 
 * @date 14/5/2016
 *
 * @section PURPOSE
 *
 *
 * @section DESCRIPTION
 */

#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QDir>
#include "classes.h"


/**
 * @class Database
 * @brief Classe responsavel por as interacçoes com a base de dados.
 */
class Database
{

public:

    QSqlDatabase mydb;

    Database();

    bool connOpen();
    void connClose();


    /**
     * Adiciona album a BD.
     *
     * @param newAlbum Ponteiro para o album.
     *
     * @return Confirmação de sucesso.
     */
    bool addAlbum(Album *newAlbum);


    /**
     * Remove album da BD.
     *
     * @param album Ponteiro para o album.
     *
     * @return Confirmação de sucesso.
     */
    bool removeAlbum(Album *album);


    /**
     * Adiciona musica a BD.
     *
     * @param newSong Ponteiro para a musica.
     *
     * @return Confirmação de sucesso.
     */
    bool addSong(Musica *newSong);


    /**
     * Adiciona autor a BD.
     *
     * @param newArtist Ponteiro para o autor.
     *
     * @return Confirmação de sucesso.
     */
    bool addArtist(Autor *newArtist);


    /**
     * Adiciona playlist a BD.
     *
     * @param newPlaylist Ponteiro para a playlist.
     *
     * @return Confirmação de sucesso.
     */
    bool addPlaylist(Playlist *newPlaylist);
};

#endif // DATABASE_H
