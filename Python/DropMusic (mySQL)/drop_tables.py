import psycopg2
import sys

def drop_tables():
    """ delete tables in the PostgreSQL database"""
    commands = (
        """
        DROP TABLE album CASCADE
        """,
        """
        DROP TABLE musica_ficheiro CASCADE
        """,
        """
        DROP TABLE compositor CASCADE
        """,
        """
        DROP TABLE autor CASCADE
        """,
        """
        DROP TABLE concerto CASCADE
        """,
        """
        DROP TABLE criticamusica CASCADE
        """,
        """
        DROP TABLE utilizador CASCADE
        """,
        """
        DROP TABLE playlist CASCADE
        """,
        """
        DROP TABLE grupomusical CASCADE
        """,
        """
        DROP TABLE artista CASCADE
        """,
        """
        DROP TABLE editora CASCADE
        """,
        """
        DROP TABLE periodoeditora CASCADE
        """,
        """
        DROP TABLE criticaalbum CASCADE
        """,
        """
        DROP TABLE musica_ficheiro_concerto CASCADE
        """,
        """
        DROP TABLE grupomusical_artista CASCADE
        """,
        """
        DROP TABLE musica_ficheiro_utilizador  CASCADE
        """,
        """
        DROP TABLE musica_ficheiro_playlist  CASCADE
        """,
        """
        DROP TABLE musica_ficheiro_genero CASCADE
        """,
        """
        DROP TABLE musica_ficheiro_album CASCADE
        """,
        """
        DROP TABLE genero CASCADE
        """,
        """
        DROP TABLE utilizador_musica_ficheiro CASCADE
        """)

    try:

        conn = psycopg2.connect(host="localhost",database="dropmusic", user="postgres", password="postgres")
        cur = conn.cursor()
        # DROP table one by one
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
    drop_tables()
