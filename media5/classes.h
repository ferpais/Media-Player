/**
 * @file classes.h
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

#ifndef CLASSES_H
#define CLASSES_H

#include <QList>
#include <QString>
#include <QDate>
#include <QDir>
#include <QFile>
#include <algorithm>

using namespace std;

/**
 * Get the RF frequency.
 *
 * @param frequency the frequency of RF transmission in MHz (2400..2525).
 *
 * @return the frequency of RF transmission in MHz (2400..2525).
 */


/**
 * @class Autor
 * @brief Classe responsavel por as interacçoes com autores.
 */
class Autor
{
private:
    QDate _dataAdicao;
    int _idBD;
    QString _imagem;
    QString _nome;
    QString _nacionalidade;
    QDate _dataNascimento;
public:

    /**
     * Falta.                                                                          !!!!!!
     */
    Autor();


    /**
     * Falta.                                                                          !!!!!!
     */
    ~Autor();


    /**
     * Vai buscar a data de adição do autor.
     *
     * @return A data de adição.
     */
    QDate getDataAdicao();


    /**
     * Define a data de adição do autor.
     *
     * @param data Data de adição.
     *
     * @return Confirmação de sucesso.
     */
    int setDataAdicao(QDate data);


    /**
     * Vai buscar o id da BD do autor.
     *
     * @return O id da BD.
     */
    int getIdBD();

    /**
     * Define o id da BD do autor.
     *
     * @param id Id da BD.
     *
     * @return Confirmação de sucesso.
     */
    int setIdBD(int id);


    /**
     * Vai buscar a imagem associada ao autor.
     *
     * @return A imagem associada ao autor.
     */
    QString getImagem();


    /**
     * Define a imagem associada ao autor.
     *
     * @param imagem Imagem a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setImagem(QString imagem);


    /**
     * Vai buscar o nome do autor.
     *
     * @return O nome do autor.
     */
    QString getNome();


    /**
     * Define o nome associada ao autor.
     *
     * @param nome Nome a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setNome(QString nome);


    /**
     * Vai buscar a nacionalidade do autor.
     *
     * @return A nacionalidade do autor.
     */
    QString getNacionalidade();


    /**
     * Define a nacionalidade associada ao autor.
     *
     * @param nacionalidade Nacionalidade a associar.
     *
     * @return Confirmação de sucesso.
     */ 
    int setNacionalidade(QString nacionalidade);


    /**
     * Vai buscar a data de nascimento do autor.
     *
     * @return A data de nascimento do autor.
     */
    QDate getDataNascimento();


    /**
     * Define a data de nascimento associada ao autor.
     *
     * @param data Data de nascimento a associar.
     *
     * @return Confirmação de sucesso.
     */ 
    int setDataNascimento(QDate data);


    /**
     * Criar Autor.
     *
     * @return Confirmação de sucesso.
     */
    int criar();


    /**
     * Apagar Autor.
     *
     * @return Confirmação de sucesso.
     */
    int apagar();


    /**
     * Reproduzir musicas associadas ao autor.
     *
     * @return Confirmação de sucesso.
     */
    int play();


    /**
     * Procurar.
     *
     * @return Confirmação de sucesso.
     */
    bool procurar(QString procura);

};



/**
 * @class Musica
 * @brief Classe responsavel por as interacçoes com musicas.
 */
class Musica
{
private:
    QDate _dataAdicao;
    int _idBD;
    QString _nome;
    QString _diretoria;
    QList <Autor*>* _autor;
    QString _genero;
    int _faixa;
public:

    /**
     * Falta.                                                                          !!!!!!
     */
    Musica();


     /**
      * Falta.                                                                         !!!!!!
      */
    ~Musica();

    /**
     * Vai buscar a data de adição da musica.
     *
     * @return A data de adição.
     */
    QDate getDataAdicao();


    /**
     * Define a data de adição da musica.
     *
     * @param data Data de adição.
     *
     * @return Confirmação de sucesso.
     */
    int setDataAdicao(QDate data);


    /**
     * Vai buscar o id da BD da musica.
     *
     * @return O id da BD.
     */
    int getIdBD();

    /**
     * Define o id da BD da musica.
     *
     * @param id Id da BD.
     *
     * @return Confirmação de sucesso.
     */
    int setIdBD(int id);


    /**
     * Vai buscar o nome da musica.
     *
     * @return O nome da musica.
     */
    QString getNome();


    /**
     * Define o nome associada a musica.
     *
     * @param nome Nome a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setNome(QString nome);


    /**
     * Vai buscar a diretoria.
     *
     * @return O nome da diretoria.
     */
    QString getDiretoria();


    /**
     * Define a diretoria da musica.
     *
     * @param diretoria Nome da diretoria.
     *
     * @return Confirmação de sucesso.
     */
    int setDiretoria(QString diretoria);

    /**
     * Vai buscar o/os autor/autores associados a musica.
     *
     * @param autores Ponteiro para lista de autores.                                   what??? para que serve essa entrada
     *
     * @return Confirmação de sucesso.
     */
    int getAutor(QList <Autor*> *autores);

    /**
     * Define o/os autor/autores associados a musica.
     *
     * @param autores Ponteiro para lista de autores.
     *
     * @return Confirmação de sucesso.
     */
    int setAutor(QList <Autor*> *autores);


    /**
     * Adiciona um autor a musica.
     *
     * @param autor Ponteiro para o autor.
     *
     * @return Confirmação de sucesso.
     */
    int addAutor(Autor *autor);


    /**
     * Remove um autor a musica.
     *
     * @param *autor Ponteiro para o autor.
     *
     * @return Confirmação de sucesso.
     */
    int removeAutor(Autor *autor);


    /**
     * Verifica se a musica tem um certo autor associado.
     *
     * @param *autor Ponteiro para o autor.
     *
     * @return Confirmação de existencia do autor.
     */
    bool hasAutor(Autor *autor);


    /**
     * Vai buscar o genero associado a musica.                                            
     *
     * @return Genero da musica.
     */
    QString getGenero();


    /**
     * Define o genero associado a musica.
     *
     * @param genero Genero da musica.
     *
     * @return Confirmação de sucesso.
     */
    int setGenero(QString genero);

    /**
     * Vai buscar o numero de faixa associados a musica.                                            
     *
     * @return Numero da faixa.
     */
    int getFaixa();


    /**
     * Define o numero de faixa associado a musica.
     *
     * @param faixa Numero da faixa.
     *
     * @return Confirmação de sucesso.
     */
    int setFaixa(int faixa);


    /**
     * Acede á informação da tag
     *
     * @param dir
     *
     * @return Algo inteiro.
     */
    int retrieveInfo(QString dir);


    /**
     * Cria directoria para musica.
     *
     * @return Confirmação de sucesso.
     */
    int criar(QString diretoria);


    /**
     * Apaga musica.
     *
     * @return Confirmação de sucesso.
     */
    int apagar();


    /**
     * Reproduz a musica.
     *
     * @return Confirmação de sucesso.
     */
    int play();


    /**
     * Procura algo nas muicas.
     *
     * @param procura Algo para procurar nos dados das musicas.
     *
     * @return Confirmação de sucesso na procura.
     */
    bool procurar(QString procura);

};


/**
 * @class Album
 * @brief Classe responsavel por todas as interacçoes com Albums.
 */
class Album
{
private:
    QDate _dataAdicao;
    int _idBD;
    QString _nome;
    QString _descricao;
    QString _diretoria;
    QString _genero;
    QString _imagem;
    int _ano;
    QList <Autor*> *_autor;
    QList <Musica*> *_musica;
public:
    /**
     * Falta.                                                                          !!!!!!
     */
    Album();

    /**
     * Falta.                                                                          !!!!!!
     */
    ~Album();

    /**
     * Vai buscar a data de adição do album.
     *
     * @return A data de adição.
     */
    QDate getDataAdicao();


    /**
     * Define a data de adição do album.
     *
     * @param data Data de adição.
     *
     * @return Confirmação de sucesso.
     */
    int setDataAdicao(QDate data);


    /**
     * Vai buscar o id da BD do album.
     *
     * @return O id da BD.
     */
    int getIdBD();

    /**
     * Define o id da BD do album.
     *
     * @param id Id da BD.
     *
     * @return Confirmação de sucesso.
     */
    int setIdBD(int id);


    /**
     * Vai buscar o nome da album.
     *
     * @return O nome do album.
     */
    QString getNome();


    /**
     * Define o nome associada ao album.
     *
     * @param nome Nome a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setNome(QString nome);


    /**
     * Vai buscar a decrição do album.
     *
     * @return O nome do album.
     */
    QString getDescricao();


    /**
     * Define a decrição do album.
     *
     * @param descricao Descrição a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setDescricao(QString descricao);


    /**
     * Vai buscar a diretoria.
     *
     * @return O nome da diretoria.
     */
    QString getDiretoria();


    /**
     * Define a diretoria do album.
     *
     * @param diretoria Nome da diretoria.
     *
     * @return Confirmação de sucesso.
     */
    int setDiretoria(QString diretoria);

    /**
     * Vai buscar o genero associado ao album.                                            
     *
     * @return Genero do album.
     */
    QString getGenero();


    /**
     * Define o genero associado ao album.
     *
     * @param genero Genero do album.
     *
     * @return Confirmação de sucesso.
     */
    int setGenero(QString genero);


    /**
     * Vai buscar o/os autor/autores associados ao album.
     *
     * @param autores Ponteiro para lista de autores.                                   what??? para que serve essa entrada
     *
     * @return Confirmação de sucesso.
     */
    int getAutor(QList <Autor*> *autores);


    /**
     * Define o/os autor/autores associados ao album.
     *
     * @param autores Ponteiro para lista de autores.
     *
     * @return Confirmação de sucesso.
     */
    int setAutor(QList <Autor*> *autores);


    /**
     * Verifica se o album tem um certo autor associado.
     *
     * @param autor Ponteiro para o autor.
     *
     * @return Confirmação de existencia do autor.
     */
    bool hasAutor(Autor *autor);


    /**
     * Vai buscar a imagem associada ao album.
     *
     * @return A imagem associada ao album.
     */
    QString getImagem();


    /**
     * Define a imagem associada ao album.
     *
     * @param imagem Imagem a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setImagem(QString imagem);


    /**
     * Vai buscar o ano de lançamento associado ao album.
     *
     * @return Ano de lançamento do album.
     */
    int getAno();


    /**
     * Define o ano do lançamento album.
     *
     * @param ano Ano de lançamento do album.
     *
     * @return Confirmação de sucesso.
     */
    int setAno(int ano);


    /**
     * Vai buscar a lista de musicas associada ao album.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int getMusicas(QList <Musica*> *musicas);


    /**
     * Define a lista de musicas associada ao album.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int setMusicas(QList <Musica*> *musicas);

    /**
     * Apaga o album.
     *
     * @return Confirmação de sucesso.
     */
    int apagar();

    /**
     * Remove uma musica do album.
     *
     * @param musica Ponteiro para a musica.
     *
     * @return Confirmação de sucesso.
     */
    int remover(Musica *musica);


    /**
     * Remove uma lista de musicas do album.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int remover(QList <Musica*> *musicas);


    /**
     * Reproduz o album.
     *
     * @return Confirmação de sucesso.
     */
    int play();


    /**
     * Adiciona uma musica ao album.
     *
     * @param musica Ponteiro para a musica.
     *
     * @return Confirmação de sucesso.
     */
    int adicionar(Musica *musica);


    /**
     * Procura algo no album.
     *
     * @param procura Algo para procurar nos dados do album.
     *
     * @return Confirmação de sucesso na procura.
     */
    bool procurar(QString procura);


    /**
     * Cria um album em determinada diretoria 
     *
     * @param diretoria Diretoria onde o album vai ser criado.
     *
     * @return Confirmação de sucesso.
     */
    int criar(QString diretoria);
    
};


/**
 * @class Playlist
 * @brief Classe responsavel por as interacçoes com Playlists.
 */
class Playlist
{
private:
    QDate _dataAdicao;
    int _idBD;
    QString _nome;
    QString _descricao;
    QList <Musica*>* _musica;
public:
    /**
     * Falta.                                                                          !!!!!!
     */
    Playlist();


    /**
     * Falta.                                                                          !!!!!!
     */
    ~Playlist();


    /**
     * Vai buscar a data de adição da playlist.
     *
     * @return A data de adição.
     */
    QDate getDataAdicao();


    /**
     * Define a data de adição do playlist.
     *
     * @param data Data de adição.
     *
     * @return Confirmação de sucesso.
     */
    int setDataAdicao(QDate data);


    /**
     * Vai buscar o id da BD da playlist.
     *
     * @return O id da BD.
     */
    int getIdBD();

    /**
     * Define o id da BD da playlist.
     *
     * @param id Id da BD.
     *
     * @return Confirmação de sucesso.
     */
    int setIdBD(int id);


    /**
     * Vai buscar o nome da playlist.
     *
     * @return O nome da playlist.
     */
    QString getNome();


    /**
     * Define o nome associada a playlist.
     *
     * @param nome Nome a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setNome(QString nome);


    /**
     * Vai buscar a decrição da playlist.
     *
     * @return O nome da playlist.
     */
    QString getDescricao();


    /**
     * Define a decrição da playlist.
     *
     * @param descricao Descrição a associar.
     *
     * @return Confirmação de sucesso.
     */
    int setDescricao(QString descricao);


    /**
     * Vai buscar o numero de musicas da playlist.
     *
     * @return Numero de musicas da playlist.
     */
    int getSize();


    /**
     * Vai buscar a lista de musicas da playlist.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int getMusicas(QList <Musica*> *musicas);


    /**
     * Vai buscar a musica da playlist com determinado indice .
     *
     * @param indice Indice da musica.
     *
     * @return Musica do indice
     */
    Musica *getMusica(int indice);


    /**
     * Define a lista de musicas associada a playlist.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int setMusicas(QList <Musica*> *musicas);


    /**
     * Apaga a playlist.
     *
     * @return Confirmação de sucesso.
     */
    int apagar();


    /**
     * Reproduz a playlist.
     *
     * @return Confirmação de sucesso.
     */
    int play();


    /**
     * Adiciona musica a playlist.
     *
     * @param musica Musica a adicionar.
     *
     * @return Confirmação de sucesso.
     */
    int adicionar(Musica* musica);


    /**
     * Remove musica da playlist.
     *
     * @param musica Musica a remover.
     *
     * @return Confirmação de sucesso.
     */
    int remover(Musica* musica);


    /**
     * Procura musica na playlist.
     *
     * @param musica Musica a procura.
     *
     * @return Confirmação de sucesso na procura.
     */
    bool procurar(QString procura);


    /**
     * Cria uma playlist.
     *
     * @return Confirmação de sucesso.
     */
    int criar();
    
};




/**
 * @class Player
 * @brief Classe responsavel por as interacçoes com o player.
 */
class Player
{
private:
    Playlist* _lista;
    QList <int> _ordem;
    int _aTocar;
    bool _aleatorio;
public:

    /**
     * Falta.                                                                          !!!!!!
     */
    Player();


    /**
     * Falta.                                                                          !!!!!!
     */
    ~Player();


    /**
     * Vai buscar a lista de musicas para reproduzir.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int getMusicas(QList <Musica*> *lista);


    /**
     * Reproduz as musicas.
     *
     * @return Confirmação de sucesso.
     */
    int play();


    /**
     * Pausa a reprodução actual.
     *
     * @return Confirmação de sucesso.
     */   
    int pausa();


    /**
     * Para a reprodução actual.
     *
     * @return Confirmação de sucesso.
     */       
    int parar();


    /**
     * Reproduz a musica seguinte.
     *
     * @return Confirmação de sucesso.
     */   
    int seguinte();


    /**
     * Reproduz a musica anterior.
     *
     * @return Confirmação de sucesso.
     */ 
    int anterior();

    /**
     * Altera o modo de reprodução de musicas para modo aletorio.
     *
     * @return Confirmação de sucesso.
     */    
    int aleatorio(bool aleatorio);


    /**
     * Adiciona a playlist uma lista de musicas.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */
    int adicionar(QList <Musica*> *musicas);


    /**
     * Adiciona a playlist uma  musicas.
     *
     * @param musica Ponteiro para a musica.
     *
     * @return Confirmação de sucesso.
     */
    int adicionar(Musica *musicas);


    /**
     * Remove da playlist uma lista de musicas.
     *
     * @param musicas Ponteiro para a lista de musicas.
     *
     * @return Confirmação de sucesso.
     */    
    int remover(QList <Musica*> *musicas);


    /**
     * Remove da playlist todas as musicas.
     *
     * @return Confirmação de sucesso.
     */        
    int removerTodas();


    /**
     * Verifica se playlist não tem musicas.
     *
     * @return Confirmação de vazio.
     */      
    bool isEmpty();


    /**
     * Verifica se o modo de reprodução actual é o modo aleatorio.
     *
     * @return Confirmação de random.
     */      
    bool isRandom();
    
};

#endif // CLASSES_H
