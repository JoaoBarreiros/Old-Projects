import psycopg2
import sys

def create_tables():
    """ create tables in the PostgreSQL database"""
    commands = (
        """
        CREATE TABLE album (
            nomealbum	 VARCHAR(512) NOT NULL,
            datacriacao	 TIMESTAMP NOT NULL,
            numeromusicas INTEGER NOT NULL,
            tempototal	 FLOAT(8),
            albumid	 SERIAL,
            autor_autorid INTEGER NOT NULL,
            PRIMARY KEY(albumid)
        );
        """,
        """
        CREATE TABLE musica_ficheiro (
                musicaid		 SERIAL,
                nomemusica		 VARCHAR(512) NOT NULL,
                datalancamento		 TIMESTAMP NOT NULL,
                informacoes		 TEXT,
                duracao			 FLOAT(8) NOT NULL,
                letra			 TEXT,
                estudiogravacao		 VARCHAR(512) NOT NULL,
                ficheiro_nomeficheiro	 VARCHAR(512) UNIQUE NOT NULL,
                ficheiro_tamanhoficheiro INTEGER NOT NULL,
                ficheiro_tipoficheiro	 VARCHAR(512) NOT NULL,
                ficheiro_icone		 BYTEA,
                autor_autorid		 INTEGER NOT NULL,
                PRIMARY KEY(musicaid)
        );
        """,
        """
        CREATE TABLE compositor (
                cccompositor	 CHAR(8) UNIQUE NOT NULL,
                nomecompositor VARCHAR(512) NOT NULL,
                datainicial	 DATE,
                datafinal	 DATE,
                datanascimento DATE,
                autor_autorid	 INTEGER UNIQUE NOT NULL,
                PRIMARY KEY(autor_autorid)
        );
        """,
        """
        CREATE TABLE autor (
                autorid		 SERIAL,
                biografia		 TEXT,
                nacionalidade	 VARCHAR(512),
                datainicialatividade DATE,
                paginaweb		 VARCHAR(512),
                nomeautor		 VARCHAR(512) NOT NULL,
                datafinalatividade	 DATE,
                PRIMARY KEY(autorid)
        );
        """,
        """
        CREATE TABLE genero (
                tipo	 VARCHAR(512) UNIQUE NOT NULL,
                descricao TEXT,
                PRIMARY KEY(tipo)
        );
        """,
        """
        CREATE TABLE concerto (
                localidade	 VARCHAR(512) UNIQUE NOT NULL,
                data	 DATE UNIQUE NOT NULL,
                nomeconcerto VARCHAR(512),
                lotacao	 INTEGER,
                precobilhete DOUBLE PRECISION,
                autor_autorid INTEGER NOT NULL,
                PRIMARY KEY(localidade,data)
        );
        """,
        """
        CREATE TABLE criticamusica (
                datahora	 TIMESTAMP UNIQUE NOT NULL,
                texto		 TEXT NOT NULL,
                pontuacao	 INTEGER NOT NULL,
                utilizador_email VARCHAR(512),
                musica_musicaid	 INTEGER,
                PRIMARY KEY(datahora,utilizador_email,musica_musicaid)
        );
        """,
        """
        CREATE TABLE utilizador (
                nomeutilizador VARCHAR(512) UNIQUE NOT NULL,
                palavrapasse	 VARCHAR(512) NOT NULL,
                tipoutilizador BOOL NOT NULL DEFAULT false,
                email		 VARCHAR(512) UNIQUE NOT NULL,
                datanascimento DATE,
                primeironome	 VARCHAR(512),
                ultimonome	 VARCHAR(512),
                pais		 VARCHAR(512),
                genero	 VARCHAR(512),
                dataregisto	 DATE NOT NULL,
                PRIMARY KEY(email)
        );
        """,
        """
        CREATE TABLE playlist (
            nomeplaylist	 VARCHAR(512) UNIQUE NOT NULL,
            datacriacao	 TIMESTAMP UNIQUE NOT NULL,
            tipoplaylist	 BOOL NOT NULL DEFAULT false,
            numeromusicas	 INTEGER,
            playlistid	 SERIAL,
            utilizador_email VARCHAR(512) NOT NULL,
            PRIMARY KEY(playlistid)
        );
        """,
        """
        CREATE TABLE grupomusical (
            numeromembros INTEGER NOT NULL,
            autor_autorid   INTEGER UNIQUE NOT NULL,
            PRIMARY KEY(autor_autorid)
        );
        """,
        """
        CREATE TABLE artista (
                datanascimento DATE NOT NULL,
                pseudonimo	 VARCHAR(512),
                ccartista	 CHAR(8) UNIQUE NOT NULL,
                autor_autorid	  INTEGER UNIQUE NOT NULL,
                PRIMARY KEY(autor_autorid)
        );
        """,
        """
        CREATE TABLE editora (
                editoranome	 VARCHAR(512) UNIQUE NOT NULL,
                datafundacao TIMESTAMP UNIQUE NOT NULL,
                descricao	 TEXT,
                PRIMARY KEY(editoranome,datafundacao)
        );
        """,
        """
        CREATE TABLE periodoeditora (
                datainicio		 DATE UNIQUE NOT NULL,
                datafim		 DATE UNIQUE NOT NULL,
                editora_editoranome	 VARCHAR(512),
                editora_datafundacao TIMESTAMP,
                autor_autorid	 INTEGER,
                PRIMARY KEY(datainicio,datafim,editora_editoranome,editora_datafundacao,autor_autorid)
        );
        """,
        """
        CREATE TABLE criticaalbum (
            datahora	 TIMESTAMP,
            texto	TEXT NOT NULL,
            pontuacao	 INTEGER NOT NULL,
            utilizador_email VARCHAR(512),
            album_albumid	 INTEGER,
            PRIMARY KEY(datahora,utilizador_email,album_albumid)
        );
        """,
        """
        CREATE TABLE musica_ficheiro_concerto (
                musica_ficheiro_musicaid INTEGER,
                concerto_localidade	 VARCHAR(512),
                concerto_data		 DATE,
                PRIMARY KEY(musica_ficheiro_musicaid,concerto_localidade,concerto_data)
        );
        """,
        """
        CREATE TABLE grupomusical_artista (
                grupomusical_autor_autorid INTEGER NOT NULL,
                artista_autor_autorid	 INTEGER,
                PRIMARY KEY(artista_autor_autorid)
        );
        """,
        """
        CREATE TABLE musica_ficheiro_utilizador (
                musica_ficheiro_musicaid INTEGER,
                utilizador_email	 VARCHAR(512),
                PRIMARY KEY(musica_ficheiro_musicaid,utilizador_email)
        );
        """,
        """
        CREATE TABLE musica_ficheiro_playlist (
            musica_ficheiro_musicaid INTEGER,
            playlist_playlistid	 INTEGER,
            PRIMARY KEY(musica_ficheiro_musicaid,playlist_playlistid)
        );
        """,
        """
        CREATE TABLE musica_ficheiro_genero (
                musica_ficheiro_musicaid INTEGER NOT NULL UNIQUE,
                genero_tipo		 VARCHAR(512),
                PRIMARY KEY(musica_ficheiro_musicaid,genero_tipo)
        );
        """,
        """
        CREATE TABLE musica_ficheiro_album (
            musica_ficheiro_musicaid INTEGER,
            album_albumid		 INTEGER,
            PRIMARY KEY(musica_ficheiro_musicaid,album_albumid)
        );
        """,
        """
        CREATE TABLE utilizador_musica_ficheiro (
            utilizador_email	 VARCHAR(512),
            musica_ficheiro_musicaid INTEGER,
            PRIMARY KEY(utilizador_email,musica_ficheiro_musicaid)
        );
        """)

    try:

        conn = psycopg2.connect(host="localhost",database="dropmusic", user="postgres", password="postgres")
        cur = conn.cursor()
        # create table one by one
        for command in commands:
            cur.execute(command)
        # close communication with the PostgreSQL database server
        cur.close()
        # commit the changes
        conn.commit()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
 
 
if __name__ == '__main__':
    create_tables()
