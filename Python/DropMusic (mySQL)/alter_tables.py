import psycopg2
import sys

def alter_tables():
    """ alter tables in the PostgreSQL database"""
    commands = (
        """
        ALTER TABLE album ADD CONSTRAINT album_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE album ADD CONSTRAINT AlbumNome CHECK (NomeAlbum = initcap(NomeAlbum));
        """,
        """
        ALTER TABLE album ADD CONSTRAINT NumeroMusicasValido CHECK (NumeroMusicas > 0);
        """,
        """
        ALTER TABLE album ADD CONSTRAINT DataCriacaoPossivel CHECK (DataCriacao <= current_timestamp);
        """,
        """
        ALTER TABLE album ADD CONSTRAINT TempoTotalPossivel CHECK (TempoTotal > 0);
        """,
        """
        ALTER TABLE musica_ficheiro ADD CONSTRAINT musica_ficheiro_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro ADD CONSTRAINT DataPossivelMax CHECK (DataLancamento <= current_timestamp);
        """,
        """
        ALTER TABLE musica_ficheiro ADD CONSTRAINT MusicaNome CHECK (NomeMusica = initcap(NomeMusica));
        """,
        """
        ALTER TABLE musica_ficheiro ADD CONSTRAINT DuracaoPossivel CHECK (Duracao > 0);
        """,
        """
        ALTER TABLE musica_ficheiro ADD CONSTRAINT EstudioGravacaoNome CHECK (EstudioGravacao = initcap(EstudioGravacao));
        """,
        """
        ALTER TABLE compositor ADD CONSTRAINT compositor_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE compositor ADD CONSTRAINT CompositorNome CHECK (NomeCompositor = initcap(NomeCompositor));
        """,
        """
        ALTER TABLE compositor ADD CONSTRAINT DataInicialValida CHECK (DataInicial <= current_date);
        """,
        """
        ALTER TABLE compositor ADD CONSTRAINT DataNascimentoValida CHECK (DataNascimento <= current_date);
        """,
        """
        ALTER TABLE autor ADD CONSTRAINT NacionalidadeVerificacao CHECK (Nacionalidade = initcap(Nacionalidade));
        """,
        """
        ALTER TABLE autor ADD CONSTRAINT DatainicialAtividadeVálida CHECK (DatainicialAtividade <= current_date);
        """,
        """
        ALTER TABLE autor ADD CONSTRAINT NomeAutorValido CHECK (NomeAutor = initcap(NomeAutor));
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT concerto_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT LocalidadeNome CHECK (Localidade = initcap(Localidade));
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT DataPossivel CHECK (Data <= current_date);
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT ConcertoNome CHECK (NomeConcerto = initcap(NomeConcerto));
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT LotacaoNumero CHECK (Lotacao > 0); 
        """,
        """
        ALTER TABLE concerto ADD CONSTRAINT PreçoBilheteValido CHECK (PrecoBilhete >= 0);
        """,
        """
        ALTER TABLE criticamusica ADD CONSTRAINT criticamusica_fk1 FOREIGN KEY (utilizador_email) REFERENCES utilizador(email) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE criticamusica ADD CONSTRAINT criticamusica_fk2 FOREIGN KEY (musica_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE criticamusica ADD CONSTRAINT DataHoraValidas CHECK (DataHora <= current_timestamp);
        """,
        """
        ALTER TABLE criticamusica ADD CONSTRAINT PontuacaoValida CHECK (Pontuacao >= 0);
        """,
        """
        ALTER TABLE utilizador ADD CONSTRAINT DataNascimentoValidaMax CHECK (DataNascimento <= current_date);
        """,
        """
        ALTER TABLE utilizador ADD CONSTRAINT PrimeiroNomeVerificacao CHECK (PrimeiroNome = upper(PrimeiroNome));
        """,
        """
        ALTER TABLE utilizador ADD CONSTRAINT UltimoNomeVerificacao CHECK (UltimoNome = upper(UltimoNome));
        """,
        """
        ALTER TABLE utilizador ADD CONSTRAINT PaisVerificacao CHECK (Pais = initcap(Pais));
        """,
        """
        ALTER TABLE utilizador ADD CONSTRAINT DataRegistoValida CHECK (DataRegisto <= current_date);
        """,
        """
        ALTER TABLE playlist ADD CONSTRAINT playlist_fk1 FOREIGN KEY (utilizador_email) REFERENCES utilizador(email) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE playlist ADD CONSTRAINT PlaylistNome CHECK (NomePlaylist = initcap(NomePlaylist));
        """,
        """
        ALTER TABLE playlist ADD CONSTRAINT NumeroMusicasValido CHECK (NumeroMusicas >= 0);
        """,
        """
        ALTER TABLE playlist ADD CONSTRAINT DataCriacaoValida CHECK (DataCriacao <= current_timestamp);
        """,
        """
        ALTER TABLE grupomusical ADD CONSTRAINT grupomusical_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE grupomusical ADD CONSTRAINT NumeroMembrosValido CHECK (NumeroMembros > 0);
        """,
        """
        ALTER TABLE artista ADD CONSTRAINT artista_fk1 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE artista ADD CONSTRAINT DataNascimentoPossivel CHECK (DataNascimento <= current_date);
        """,
        """
        ALTER TABLE artista ADD CONSTRAINT PseudonimoNome CHECK (Pseudonimo = initcap(Pseudonimo));
        """,
        """
        ALTER TABLE periodoeditora ADD CONSTRAINT periodoeditora_fk1 FOREIGN KEY (editora_editoranome) REFERENCES editora(editoranome) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE periodoeditora ADD CONSTRAINT periodoeditora_fk2 FOREIGN KEY (editora_datafundacao) REFERENCES editora(datafundacao) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE periodoeditora ADD CONSTRAINT periodoeditora_fk3 FOREIGN KEY (autor_autorid) REFERENCES autor(autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE periodoeditora ADD CONSTRAINT DataInicialValida CHECK (DataInicio <= current_date);
        """,
        """
        ALTER TABLE criticaalbum ADD CONSTRAINT criticaalbum_fk1 FOREIGN KEY (utilizador_email) REFERENCES utilizador(email) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE criticaalbum ADD CONSTRAINT criticaalbum_fk2 FOREIGN KEY (album_albumid) REFERENCES album(albumid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE criticaalbum ADD CONSTRAINT DataHoraValidas CHECK (DataHora <= current_timestamp);
        """,
        """
        ALTER TABLE criticaalbum ADD CONSTRAINT PontuacaoValida CHECK (Pontuacao >= 0);
        """,
        """
        ALTER TABLE musica_ficheiro_concerto ADD CONSTRAINT musica_ficheiro_concerto_fk1 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_concerto ADD CONSTRAINT musica_ficheiro_concerto_fk2 FOREIGN KEY (concerto_localidade) REFERENCES concerto(localidade) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_concerto ADD CONSTRAINT musica_ficheiro_concerto_fk3 FOREIGN KEY (concerto_data) REFERENCES concerto(data) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE grupomusical_artista ADD CONSTRAINT grupomusical_artista_fk1 FOREIGN KEY (grupomusical_autor_autorid) REFERENCES grupomusical(autor_autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE grupomusical_artista ADD CONSTRAINT grupomusical_artista_fk2 FOREIGN KEY (artista_autor_autorid) REFERENCES artista(autor_autorid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_utilizador ADD CONSTRAINT musica_ficheiro_utilizador_fk1 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_utilizador ADD CONSTRAINT musica_ficheiro_utilizador_fk2 FOREIGN KEY (utilizador_email) REFERENCES utilizador(email) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_playlist ADD CONSTRAINT musica_ficheiro_playlist_fk1 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_playlist ADD CONSTRAINT musica_ficheiro_playlist_fk2 FOREIGN KEY (playlist_playlistid) REFERENCES playlist(playlistid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_genero ADD CONSTRAINT musica_ficheiro_genero_fk1 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_genero ADD CONSTRAINT musica_ficheiro_genero_fk2 FOREIGN KEY (genero_tipo) REFERENCES genero(tipo) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_album ADD CONSTRAINT musica_ficheiro_album_fk1 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE musica_ficheiro_album ADD CONSTRAINT musica_ficheiro_album_fk2 FOREIGN KEY (album_albumid) REFERENCES album(albumid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE utilizador_musica_ficheiro ADD CONSTRAINT utilizador_musica_ficheiro_fk1 FOREIGN KEY (utilizador_email) REFERENCES utilizador(email) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        ALTER TABLE utilizador_musica_ficheiro ADD CONSTRAINT utilizador_musica_ficheiro_fk2 FOREIGN KEY (musica_ficheiro_musicaid) REFERENCES musica_ficheiro(musicaid) ON UPDATE CASCADE ON DELETE CASCADE;
        """,
        """
        INSERT into utilizador
        values ('admin','21232f297a57a5a743894a0e4a801fc3',True,'admin','1996-11-17','ADMIN','ADMIN','Portugal','m',current_date)
        """,
        """
        INSERT into genero values
        ('Rock','Genero musical de música popular que se desenvolveu durante e após a década de 1950'),
        ('Reggae','Genero musical desenvolvido originalmente na Jamaica do fim da década de 1960'),
        ('Hip Hop','Genero musical, com uma subcultura iniciada durante a década de 1970'),
        ('Rap','É um discurso rítmico com rimas e poesias, que surgiu no final do século XX entre as comunidades Afro-descendentes nos Estados Unidos'),
        ('Pop','Um termo que deriva da abreviação de popular é um gênero da música popular que se originou durante a década de 1950 nos Estados Unidos e Reino Unido.'),
        ('EDM','Vista principalmente em casas noturnas, ou em um ambiente que é centrado na dança e entretenimento, como clubes, raves ou festas.'),
        ('Heavy Metal','Genero do rock que se desenvolveu no final da década de 1960 e no início da década de 1970, em grande parte no Reino Unido e nos Estados Unidos.'),
        ('RandB','Genero musical baseado no jazz');
        """,
        """
        INSERT into editora values
        ('East West Records','1-1-1955','East West Records (stylized as eastwest from 1990 to 2001) is a record label formed in 1955, distributed and owned by Warner Music Group, headquartered in London, United Kingdom.'),
        ('Diamond Records','1-1-1961','Diamond Records was a record label, based in New York City, which was founded in 1961 by former Roulette Records executive Joe Kolsky.Another Roulette exec, Kolskys brother Phil Kahl, joined Kolsky in the venture the following year.');
        """
        )
        

    try:

        conn = psycopg2.connect(host="localhost",database="dropmusic", user="postgres", password="postgres")
        cur = conn.cursor()
        # alter table one by one
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
    alter_tables()
