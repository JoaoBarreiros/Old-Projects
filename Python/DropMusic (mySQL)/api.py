#!/usr/bin/python
# -*- coding: latin-1 -*-

''' 
Modulo API
==========

Este modulo vai ligar-se ÃƒÂ  base de dados e fazer a interface com a aplicacao.

created by Marco SimÃƒÂµes
'''

import psycopg2


conn = None

# dados da connecÃƒÂ§ÃƒÂ£o
host = 'localhost'
database = 'dropmusic'
user = 'postgres'
password = 'postgres'

#====================================================================================================
def connect():
    # estabelece a conneccao com a bd
    global conn

    if conn == None:
        try:
            conn = psycopg2.connect(host=host,database=database, user=user, password=password)

        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
#====================================================================================================
def login(username, password):
    # verifica se existe um user com este username e password

    sql = """SELECT nomeutilizador, palavrapasse, tipoutilizador
             FROM utilizador
             WHERE nomeutilizador = %s and palavrapasse = %s"""
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (username, password, ))
        # nenhum user com esse username e password
        if cur.rowcount < 1:
            cur.close()
            return None
        
        # ir buscar a linha resultado do SQL
        data = cur.fetchone()
        user = {'nome': data[0], 'tipo': data[2]}
        cur.close()
        return user

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
#====================================================================================================    
def registo(username,password,email,datanascimento,primeironome,ultimonome,pais,genero):
# verifica se existe um user com este username e password

    sql = """SELECT nomeutilizador, palavrapasse, tipoutilizador
             FROM utilizador
             WHERE nomeutilizador = %s or email = %s"""

    sql2 = """INSERT INTO utilizador 
              VALUES (%s,%s,false,%s,%s,upper(%s),upper(%s),initcap(%s),%s,current_date)"""
    
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (username, email, ))
        
        # nenhum user com esse username ou email
        if cur.rowcount < 1:
            cur.execute(sql2, (username, password, email, datanascimento, primeironome, ultimonome, pais, genero, ))
            conn.commit()
            cur.close()
            return login(username,password)
        return None
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return None
#====================================================================================================        
def mostramusica(nome,tipo_de_pesquisa):
    #Nome
    sql1 = """SELECT m.musicaid,m.nomemusica, a.nomeautor
             FROM musica_ficheiro as m,autor as a
             WHERE m.autor_autorid = a.autorid
             and m.nomemusica like %s
             order by m.musicaid"""
    #Letra
    sql2 = """SELECT m.musicaid,m.nomemusica, a.nomeautor
             FROM musica_ficheiro as m, autor a
             WHERE m.autor_autorid = a.autorid
             and m.letra like %s
             order by m.musicaid"""
    #Concerto
    sql3 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, c.nomeconcerto, c.data
             FROM musica_ficheiro as m,autor a, musica_ficheiro_concerto as mc, concerto as c
             WHERE m.autor_autorid = a.autorid and m.musicaid = mc.musica_ficheiro_musicaid and c.localidade = mc.concerto_localidade and c.data = mc.concerto_data
             and c.nomeconcerto like %s
             order by m.musicaid"""
    #Compositor
    sql4 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, c.nomecompositor
             FROM musica_ficheiro as m, autor a, compositor as c 
             WHERE m.autor_autorid = a.autorid and c.autor_autorid = a.autorid
             and c.nomecompositor like %s
             order by m.musicaid"""
    #Pontuacao
    sql5 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, avg(cm.pontuacao)
             FROM musica_ficheiro as m,autor a, criticamusica as cm
             WHERE m.autor_autorid = a.autorid and m.musicaid = cm.musica_musicaid
             group by m.musicaid, a.nomeautor having avg(cm.pontuacao) = %s
             order by m.musicaid"""
    #DataLancamento
    sql6 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, m.datalancamento
             FROM musica_ficheiro as m, autor a
             WHERE m.autor_autorid = a.autorid
             and m.datalancamento = %s
             order by m.musicaid"""
    #Genero
    sql7 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, g.tipo
             FROM musica_ficheiro as m,autor a, genero as g, musica_ficheiro_genero as mg
             WHERE m.autor_autorid = a.autorid and m.musicaid = mg.musica_ficheiro_musicaid and g.tipo = mg.genero_tipo
             and g.tipo like %s
             order by m.musicaid"""
    #Álbum
    sql8 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, al.nomealbum
             FROM musica_ficheiro as m,autor a, album as al, musica_ficheiro_album as mal
             WHERE m.autor_autorid = a.autorid and m.musicaid = mal.musica_ficheiro_musicaid and al.albumid = mal.album_albumid
             and al.nomealbum like %s
             order by m.musicaid"""
    #Autor
    sql9 = """SELECT m.musicaid,m.nomemusica, a.nomeautor
             FROM musica_ficheiro as m,autor a
             WHERE m.autor_autorid = a.autorid
             and a.nomeautor like %s
             order by m.musicaid"""
    #Estúdio Gravação
    sql10 = """SELECT m.musicaid,m.nomemusica, a.nomeautor, m.estudiogravacao
             FROM musica_ficheiro as m,autor a
             WHERE m.autor_autorid = a.autorid
             and m.estudiogravacao = %s
             order by m.musicaid"""
    
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        if tipo_de_pesquisa == 1:
            cur.execute(sql1, (nome, ))
        elif tipo_de_pesquisa == 2:
            cur.execute(sql2, (nome, ))
        elif tipo_de_pesquisa == 3:
            cur.execute(sql3, (nome, ))
        elif tipo_de_pesquisa == 4:
            cur.execute(sql4, (nome, ))
        elif tipo_de_pesquisa == 5:
            cur.execute(sql5, (nome, ))
        elif tipo_de_pesquisa == 6:
            cur.execute(sql6, (nome, ))
        elif tipo_de_pesquisa == 7:
            cur.execute(sql7, (nome, ))
        elif tipo_de_pesquisa == 8:
            cur.execute(sql8, (nome, ))
        elif tipo_de_pesquisa == 9:
            cur.execute(sql9, (nome, ))
        elif tipo_de_pesquisa == 10:
            cur.execute(sql10, (nome, ))
        
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0,None

        # ir buscar a linha resultado do SQL
        row = cur.fetchone()
        ID = row[0]
        
        while row is not None:
            print(row)
            row = cur.fetchone()
        cur.close()
        return cur.rowcount,ID
        
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def mostraalbum(nome,tipo_de_pesquisa):
    #Pontuacao
    sql1 = """SELECT al.albumid,al.nomealbum, a.nomeautor, al.datacriacao, avg(ca.pontuacao), al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             FROM album as al, autor as a, criticaalbum as ca, musica_ficheiro as m, musica_ficheiro_album as ma, musica_ficheiro_genero as mg, criticamusica as cm
             WHERE a.autorid = al.autor_autorid and al.albumid = ca.album_albumid
             and al.albumid = ma.album_albumid
             and ma.musica_ficheiro_musicaid = m.musicaid
             and m.musicaid = cm.musica_musicaid
             and m.musicaid = mg.musica_ficheiro_musicaid
             group by al.albumid, al.nomealbum, a.nomeautor,al.datacriacao, al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             having avg(ca.pontuacao) = %s
             order by al.albumid"""
    #Autor
    sql2 = """SELECT al.albumid,al.nomealbum, a.nomeautor, al.datacriacao, al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             FROM album as al, autor as a, musica_ficheiro as m, musica_ficheiro_album as ma, musica_ficheiro_genero as mg, criticamusica as cm
             WHERE a.autorid = al.autor_autorid
             and al.albumid = ma.album_albumid
             and ma.musica_ficheiro_musicaid = m.musicaid
             and m.musicaid = cm.musica_musicaid
             and m.musicaid = mg.musica_ficheiro_musicaid
             and a.nomeautor like %s
             order by al.albumid"""
    #Nome
    sql3 = """SELECT al.albumid,al.nomealbum, a.nomeautor, al.datacriacao, al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             FROM album as al, autor as a, musica_ficheiro as m, musica_ficheiro_album as ma, musica_ficheiro_genero as mg, criticamusica as cm
             WHERE a.autorid = al.autor_autorid
             and al.albumid = ma.album_albumid
             and ma.musica_ficheiro_musicaid = m.musicaid
             and m.musicaid = cm.musica_musicaid
             and m.musicaid = mg.musica_ficheiro_musicaid
             and al.nomealbum like %s
             order by al.albumid"""
    #Data Criação
    sql4 = """SELECT al.albumid,al.nomealbum, a.nomeautor, al.datacriacao, al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             FROM album as al, autor as a, musica_ficheiro as m, musica_ficheiro_album as ma, musica_ficheiro_genero as mg, criticamusica as cm
             WHERE a.autorid = al.autor_autorid
             and al.albumid = ma.album_albumid
             and ma.musica_ficheiro_musicaid = m.musicaid
             and m.musicaid = cm.musica_musicaid
             and m.musicaid = mg.musica_ficheiro_musicaid
             and al.datacriacao = %s
             order by al.albumid"""
    #Música
    sql5 = """SELECT al.albumid,al.nomealbum, a.nomeautor, al.datacriacao, al.tempototal, m.musicaid, m.nomemusica,m.informacoes,m.duracao,m.datalancamento, m.letra, mg.genero_tipo, cm.texto
             FROM album as al, autor as a, musica_ficheiro as m, musica_ficheiro_album as ma, musica_ficheiro_genero as mg, criticamusica as cm
             WHERE a.autorid = al.autor_autorid
             and al.albumid = ma.album_albumid
             and m.musicaid = ma.musica_ficheiro_musicaid
             and m.musicaid = cm.musica_musicaid
             and m.musicaid = mg.musica_ficheiro_musicaid
             and m.nomemusica like %s
             order by al.albumid"""
   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        if tipo_de_pesquisa == 1:
            cur.execute(sql1, (nome, ))
        elif tipo_de_pesquisa == 2:
            cur.execute(sql2, (nome, ))
        elif tipo_de_pesquisa == 3:
            cur.execute(sql3, (nome, ))
        elif tipo_de_pesquisa == 4:
            cur.execute(sql4, (nome, ))
        elif tipo_de_pesquisa == 5:
            cur.execute(sql5, (nome, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0,None

        # ir buscar a linha resultado do SQL
        row = cur.fetchone()
        ID = row[0]
        
        while row is not None:
            print(row)
            row = cur.fetchone()
        cur.close()
        return cur.rowcount,ID
        
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def mostraautor(nome,tipo_de_pesquisa):
    #Nome
    sql1 = """SELECT a.nomeautor, a.biografia, a.nacionalidade
             FROM autor a
             WHERE a.nomeautor like %s
             order by a.autorid"""
    #Álbum
    sql2 = """SELECT a.nomeautor, a.biografia, a.nacionalidade, al.nomealbum
             FROM autor a, album al
             WHERE a.autorid = al.autor_autorid
             and al.nomealbum like %s
             order by a.autorid"""
    #Editora
    sql3 = """SELECT a.nomeautor, a.biografia, a.nacionalidade, e.editoranome, pe.datainicio, pe.datafim
             FROM autor a, periodoeditora pe, editora e
             WHERE a.autorid = pe.autor_autorid
             and e.editoranome = pe.editora_editoranome
             and e.datafundacao = pe.editora_datafundacao
             and e.editoranome like %s
             order by a.autorid"""
    #Concerto
    sql4 = """SELECT a.nomeautor, a.biografia, a.nacionalidade, c.nomeconcerto, c.localidade, to_char(c.data, 'DD-MM-YYYY')
             FROM autor a, concerto c
             WHERE a.autorid = c.autor_autorid
             and c.nomeconcerto like %s
             order by a.autorid"""
    
    #Nacionalidade 
    sql5 = """SELECT a.nomeautor, a.biografia, a.nacionalidade
             FROM autor a
             WHERE a.nacionalidade like %s
             order by a.autorid"""
    
   #Período de atividade
    sql6 = """SELECT a.nomeautor, a.biografia, a.nacionalidade, a.datainicialatividade, a.datafinalatividade
             FROM autor a
             WHERE a.datainicialatividade >= %s
             and a.datafinalatividade <= %s
             order by a.autorid"""

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        if tipo_de_pesquisa == 1:
            cur.execute(sql1, (nome, ))
        elif tipo_de_pesquisa == 2:
            cur.execute(sql2, (nome, ))
        elif tipo_de_pesquisa == 3:
            cur.execute(sql3, (nome, ))
        elif tipo_de_pesquisa == 4:
            cur.execute(sql4, (nome, ))
        elif tipo_de_pesquisa == 5:
            cur.execute(sql5, (nome, ))
        elif tipo_de_pesquisa == 6:
            cur.execute(sql6, (nome,nome, ))
        
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return None
        
        # ir buscar a linha resultado do SQL
        row = cur.fetchone()
        while row is not None:
            print(str(row))
            row = cur.fetchone()
 
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def mostracritica(nome,tipo_de_pesquisa):
    #Música
    sql1 = """SELECT m.nomemusica,cm.texto,cm.pontuacao
             FROM musica_ficheiro m, criticamusica cm
             WHERE m.musicaid = cm.musica_musicaid
             and m.musicaid = %s
             order by cm.datahora"""
    #Ãlbum
    sql2 = """SELECT al.nomealbum,ca.texto,ca.pontuacao
             FROM album al, criticaalbum ca
             WHERE al.albumid = ca.album_albumid
             order by ca.datahora"""
   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        if tipo_de_pesquisa == 1:
            cur.execute(sql1, (nome, ))
        elif tipo_de_pesquisa == 2:
            cur.execute(sql2, (nome, ))

        
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return None
        
        # ir buscar a linha resultado do SQL
        row = cur.fetchone()
        while row is not None:
            print(row)
            row = cur.fetchone()
 
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def existeautor(autorid):

    sql = """SELECT *
             FROM autor a
             WHERE a.autorid = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (autorid, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou autor
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None

#====================================================================================================
def existegenero(valor):

    sql = """SELECT *
             FROM genero g
             WHERE g.tipo like %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (valor, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou genero
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def existecritica(ID,tipo_de_pesquisa):

    sql1 = """SELECT *
             FROM musica_ficheiro m, criticamusica cm
             WHERE m.musicaid = cm.musica_musicaid
             and m.musicaid = %s
             """
    sql2 = """SELECT *
             FROM album al, criticaalbum ca
             WHERE al.albumid = ca.album_abumid
             and al.albumid = %s
             """
   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        if tipo_de_pesquisa == 1:
            cur.execute(sql1, (ID, ))
        elif tipo_de_pesquisa == 2:
            cur.execute(sql2, (ID, ))
            
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou critica
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def existemusica(musicaid):

    sql = """SELECT *
             FROM musica_ficheiro m
             WHERE m.musicaid = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (musicaid, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou musica
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def existealbum(albumid):

    sql = """SELECT *
             FROM album al
             WHERE al.albumid = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (albumid, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou album
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def existeplaylist(playlistid):

    sql = """SELECT *
             FROM playlist p
             WHERE p.playlistid = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (playlistid, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou album
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def inseremusica(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autorid,genero,username):

    sql1 = """INSERT INTO musica_ficheiro(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autor_autorid)
              VALUES (initcap(%s),%s,%s,%s,%s,initcap(%s),%s,%s,%s,%s);"""
    sql2 = """INSERT INTO musica_ficheiro_utilizador
              VALUES((select max(musicaid) from musica_ficheiro),(select email from utilizador where nomeutilizador = %s));
           """
    sql3 = """INSERT INTO musica_ficheiro_genero
              VALUES((select max(musicaid) from musica_ficheiro), %s);"""
    
    if conn == None:
        connect()
 
    try:
        cur = conn.cursor()
        cur.execute(sql1, (nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro, autorid, ))
        cur.execute(sql2,(username,))
        cur.execute(sql3, (genero,))
        #todos inserts corretos
        conn.commit()
        cur.close()


    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
    
#====================================================================================================
def inserecriticamusica(nome,texto,pontuacao,username):

    sql = """INSERT INTO criticamusica(datahora,texto,pontuacao,utilizador_email,musica_musicaid)
              VALUES (current_timestamp,%s,%s,(SELECT u.email FROM utilizador u WHERE u.nomeutilizador like %s), (SELECT m.musicaid FROM musica_ficheiro m WHERE m.musicaid = %s));"""    
   
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql, (texto, pontuacao, username, nome ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def inserecriticaalbum(nome,datacriacao,autorid,texto,pontuacao,username):
    
    sql = """INSERT INTO criticaalbum(datahora,texto,pontuacao,utilizador_email,album_nomealbum, album_datacriacao, album_autor_autorid)
              VALUES (current_timestamp,%s,%s,(SELECT u.email FROM utilizador WHERE u.nomeutilizador like %s),%s, %s,%s);"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql, (texto,pontuacao,username,nome,datacriacao,autorid, ))
        conn.commit()
        cur.close()
        
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def insere_compositor(cccompositor,nome,biografia,nacionalidade,dataInicio,dataFim):
    sql2 = """INSERT INTO compositor
              VALUES (%s,initcap(%s),%s,initcap(%s),%s,%s,(select max(autorid) from autor))"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(cccompositor, nome, biografia, nacionalidade, dataInicio,dataFim, ))
        conn.commit()
        cur.close()
        return None
        
    except(Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return None
#====================================================================================================
def inserir_autor(biografia,nacionalidade,dataInicio,paginaWeb,nome,dataFim):
    
    sql = """Insert Into Autor(biografia,nacionalidade,datainicialatividade,paginaweb,nomeautor,datafinalatividade)
              Values(%s,initcap(%s),%s,%s,initcap(%s),%s)"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(biografia, nacionalidade, dataInicio, paginaWeb, nome,dataFim, ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0
#====================================================================================================
def inserir_artista(datanascimento,pseudonimo,ccartista):
    
    sql = """Insert Into Artista(datanascimento,pseudonimo,ccartista,autor_autorid)
              Values(%s,initcap(%s),%s,(select max(autorid) from autor))"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(datanascimento, pseudonimo, ccartista, ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0        
#====================================================================================================
def inserir_grupomusical(numeromembros):
    
    sql = """Insert Into Grupomusical(numeromembros,autor_autorid)
              Values(%s,(select max(autorid) from autor))"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(numeromembros,))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0        
#====================================================================================================
def modifica_autor(autorid,biografia,nacionalidade,datainicial,paginaweb,nomeautor,datafinal):
    
    sql = """update autor
             set biografia = %s,
                 nacionalidade =initcap(%s),
                 datainicialatividade = %s,
                 paginaweb = %s,
                 nomeautor = initcap(%s),
                 datafinalatividade = %s
             where autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(biografia, nacionalidade, datainicial, paginaweb, nomeautor, datafinal,autorid, ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def modifica_artista(datanascimento,pseudonimo,ccartista,autorid):
    
    sql = """update artista
             set datanascimento = %s,
                 pseudonimo = initcap(%s),
                 ccartista = %s
             where autor_autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(datanascimento, pseudonimo, ccartista, autorid,  ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def modifica_grupomusical(numeromembros,autorid):
    
    sql = """update grupomusical
             set numeromembros = %s
             where autor_autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(numeromembros, autorid,  ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def modifica_compositor(ccompositor,nomecompositor,dataincial,datafinal,datanascimento,autorid):
    
    sql = """update compositor
             set cccompositor = %s,
                 nomecompositor = initcap(%s),
                 datainicial = %s,
                 datafinal = %s,
                 datanascimento = %s
             where autor_autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(ccompositor,nomecompositor,dataincial,datafinal,datanascimento,autorid,  ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#==================================================================================================== 
def remove_autor(autorid):
    
    sql = """delete from autor
             where autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(autorid, ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def remove_grupomusical(autorid):
    
    sql = """delete from grupomusical
             where autor_autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(autorid,  ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def remove_compositor(autorid):
    
    sql = """delete from compositor
             where autor_autorid = %s"""

    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(autorid, ))
        conn.commit()
        cur.close()
        return 1
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return 0         
#====================================================================================================
def modificamusica(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autorid,genero,musicaid):
    
    sql1 = """update musica_ficheiro
             set nomemusica = initcap(%s),
                 datalancamento = %s,
                 informacoes = %s,
                 duracao = %s,
                 letra = %s,
                 estudiogravacao = initcap(%s),
                 ficheiro_nomeficheiro = %s,
                 ficheiro_tamanhoficheiro = %s,
                 ficheiro_tipoficheiro = %s,
                 autor_autorid = %s
             where musicaid = %s"""

    sql2 = """update musica_ficheiro_genero
              set genero_tipo = %s
              where musica_ficheiro_musicaid = %s"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autorid, musicaid, ))
        cur.execute(sql2,(genero,musicaid,))
        #todos inserts corretos
        conn.commit()
        cur.close()


    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
     
#====================================================================================================
def removemusica(musicaid):
                    
    sql = """delete from musica_ficheiro
             where musicaid = %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(musicaid, ))
        conn.commit()
        cur.close()


    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None
         
#====================================================================================================
def inserir_album(musicaid, numeromusicas, datacriacao, nomealbum, autorid):
                    
    sql1 = """INSERT INTO album(nomealbum,datacriacao,numeromusicas,tempototal,autor_autorid)
              VALUES(initcap(%s),%s,%s,(SELECT sum(m.duracao) FROM musica_ficheiro m WHERE m.musicaid in (SELECT unnest(%s))),%s)"""
    
    sql2 = """INSERT INTO musica_ficheiro_album
              VALUES(%s,(select max(albumid) from album))"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomealbum, datacriacao, numeromusicas,musicaid, autorid, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql2,(musicaid[i], ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
         
#====================================================================================================
def modifica_album(musicaid, numeromusicas, datacriacao, nomealbum, autorid, albumid):

    sql1 = """update album
             set nomealbum = initcap(%s),
                 datacriacao = %s,
                 numeromusicas = %s,
                 autor_autorid = %s
             where albumid = %s"""
    
    sql2 = """DELETE FROM musica_ficheiro_album
              WHERE album_albumid = %s"""
    
    sql3 = """INSERT INTO musica_ficheiro_album
              VALUES(%s,(select max(albumid) from album))"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomealbum, datacriacao, numeromusicas, autorid, albumid, ))
        cur.execute(sql2,(albumid, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql3,(musicaid[i], ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
#====================================================================================================
def remove_album(albumid):

    sql = """delete from album
             where albumid = %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(albumid, ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None
#====================================================================================================
def inserir_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist, username):

    sql1 = """INSERT INTO playlist(nomeplaylist,datacriacao,tipoplaylist,numeromusicas,utilizador_email)
              VALUES(initcap(%s),current_timestamp,%s,%s,(select email from utilizador where nomeutilizador = %s))"""
    
    sql2 = """INSERT INTO musica_ficheiro_playlist
              VALUES(%s,(select max(playlistid) from playlist))"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomeplaylist, tipoplaylist, numeromusicas, username, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql2,(musicaid[i], ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
    
#===================================================================================================
def modifica_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist,playlistid):

    sql1 = """update playlist
             set nomeplaylist = initcap(%s),
                 tipoplaylist = %s,
                 numeromusicas = %s
             where playlistid = %s"""
    
    sql2 = """DELETE FROM musica_ficheiro_playlist
              WHERE playlist_playlistid = %s"""
    
    sql3 = """INSERT INTO musica_ficheiro_playlist
              VALUES(%s,(select max(playlistid) from playlist))"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomeplaylist, tipoplaylist, numeromusicas, playlistid, ))
        cur.execute(sql2,(playlistid, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql3,(musicaid[i], ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
#====================================================================================================
def modifica_playlist2(ID, playlistid):

    sql1 = """update playlist
             set numeromusicas = numeromusicas + 1
             where playlistid = %s"""
    
    sql2 = """INSERT INTO musica_ficheiro_playlist
              VALUES(%s,%s)"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(playlistid, ))
        cur.execute(sql2,(ID,playlistid, ))
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
#====================================================================================================
def remove_playlist(playlistid):

    sql = """delete from playlist
             where playlistid = %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(playlistid, ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None
#====================================================================================================
def insereutilizador(nomeutilizador,palavrapasse,tipoutilizador,email,datanascimento,primeironome,ultimonome,pais,genero):

    sql = """INSERT INTO utilizador 
              VALUES (%s,%s,%s,%s,%s,upper(%s),upper(%s),initcap(%s),%s,current_date)"""
    
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (nomeutilizador, palavrapasse, tipoutilizador, email, datanascimento, primeironome, ultimonome, pais, genero, ))
        conn.commit()
        cur.close()
        return None
    
    except (Exception, psycopg2.DatabaseError) as error:
        conn.rollback()
        print(error)
        return None
#====================================================================================================
def existeutilizador(email):
    
    sql = """SELECT *
             FROM utilizador u
             WHERE u.email like %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (email, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou album
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#====================================================================================================
def modificautilizador(nomeutilizador,palavrapasse,tipoutilizador,email,datanascimento,primeironome,ultimonome,pais,genero):
    
    sql = """update utilizador
             set nomeutilizador = initcap(%s),
                 palavrapasse = %s,
                 tipoutilizador = %s,
                 datanascimento = %s,
                 primeironome = upper(%s),
                 ultimonome = upper(%s),
                 pais = initcap(%s),
                 genero = %s
             where email like %s"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(nomeutilizador, palavrapasse, tipoutilizador, datanascimento, primeironome, ultimonome, pais, genero, email ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
#===================================================================================================
def removeutilizador(email):
    
    sql = """delete from utilizador
             where email like %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(email, ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None
#===================================================================================================
def insereconcerto(localidade,data,nomeconcerto,lotacao,precobilhete,autorid,numeromusicas,musicaid):
    
    sql1 = """INSERT INTO concerto
              VALUES(initcap(%s),%s,initcap(%s),%s,%s,%s)"""
    
    sql2 = """INSERT INTO musica_ficheiro_concerto
              VALUES(%s,%s,%s)"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(localidade, data, nomeconcerto, lotacao,precobilhete,autorid, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql2,(musicaid[i],localidade,data, ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
#===================================================================================================
def existeconcerto(localidade,data):
    
    sql = """SELECT *
             FROM concerto c
             WHERE c.localidade like %s
             AND c.data = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (localidade, data, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou album
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
#===================================================================================================
def modificaconcerto(localidade,data,nomeconcerto,lotacao,precobilhete,autorid,numeromusicas,musicaid):
    
    sql1 = """update concerto
             set nomeconcerto = initcap(%s),
                 lotacao = %s,
                 precobilhete = %s,
                 autor_autorid = %s
             where localidade like initcap(%s)
             and data = %s """
    
    sql2 = """DELETE FROM musica_ficheiro_concerto
              WHERE concerto_localidade like %s
              AND concerto_data = %s """
    
    sql3 = """INSERT INTO musica_ficheiro_concerto
              VALUES(%s,%s,%s)"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql1,(nomeconcerto, lotacao, precobilhete, autorid,  localidade, data,))
        cur.execute(sql2,(localidade,data, ))
        i = 0
        while(i < numeromusicas):
            cur.execute(sql3,(musicaid[i], localidade,data, ))
            i = i + 1
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None
    
#===================================================================================================
def removeconcerto(localidade,data):
    
    sql = """delete from concerto
             where localidade like initcap(%s)
             and data = %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(localidade,data, ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None
#===================================================================================================
def existeeditora(editoranome,datafundacao):
    
    sql = """SELECT *
             FROM editora e
             WHERE e.editoranome like %s
             AND e.datafundacao = %s
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (editoranome, datafundacao, ))

        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0
        # encontrou album
        else:
            cur.close()
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None 
#===================================================================================================
def insereeditora(editoranome,autorid,datafundacao,datainicio,datafim):
    
    sql = """INSERT INTO periodoeditora
              VALUES(%s,%s,%s,%s,%s)"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(datainicio, datafim, editoranome, datafundacao,autorid, ))
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None    
#===================================================================================================
def modificaeditora(editoranome,autorid,datafundacao,datainicio,datafim):
    
    sql = """update periodoeditora
             set datainicio = %s,
                 datafim = %s,
                 editora_editoranome = %s,
                 editora_datafundacao = %s
             where autor_autorid = %s"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(datainicio, datafim, editoranome, datafundacao,autorid, ))
            
        #todos inserts corretos
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        #1 dos inserts deu erro
        conn.rollback()
        return None    
#===================================================================================================
def removeeditora(editoranome,autorid,datafundacao,datainicio,datafim):

    sql = """delete from periodoeditora
             where datainicio = %s
             and datafim = %s
             and editora_editoranome = %s
             and editora_datafundacao = %s
             and autor_autorid = %s"""
    
    if conn == None:
        connect()
        
    try:
        cur = conn.cursor()
        cur.execute(sql,(datainicio,datafim,editoranome,datafundacao,autorid, ))
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            conn.rollback()
            return None   
#===================================================================================================
def mostrarpartilha(username):
    
    sql = """SELECT *
             FROM utilizador_musica_ficheiro um
             WHERE um.utilizador_email like (SELECT email FROM utilizador WHERE nomeutilizador like initcap(%s));
             """
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        cur.execute(sql,(username, ))
        
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return None
        
        # ir buscar a linha resultado do SQL
        row = cur.fetchone()
        while row is not None:
            print(row)
            row = cur.fetchone()
 
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
#===================================================================================================
def inserirpartilha(nomeutilizador,numeromusicas,musicaid):
    
    sql = """INSERT INTO utilizador_musica_ficheiro
             VALUES((SELECT email FROM utilizador WHERE nomeutilizador like initcap(%s)),%s)"""
    
    if conn == None:
        connect()
    try:
        cur = conn.cursor()
        i = 0
        while(i < numeromusicas):
            cur.execute(sql,(nomeutilizador,musicaid[i], ))
            i = i + 1
        conn.commit()
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        conn.rollback()
        return None
   
#===================================================================================================
def mostraplaylist(playlistid):

    sql = """SELECT p.nomeplaylist,to_char(p.datacriacao, 'DD-MM-YYYY'),p.tipoplaylist,p.numeromusicas,p.playlistid,p.utilizador_email
             FROM playlist p
             WHERE p.playlistid = %s
             AND p.tipoplaylist = TRUE
             """

   
    if conn == None:
        connect()

    try:
        cur = conn.cursor()
        cur.execute(sql, (playlistid, ))
        row = cur.fetchone() 
        
        # pesquisa sem resultados
        if cur.rowcount < 1:
            print('Pesquisa sem resultados')
            cur.close()
            return 0

        # encontrou album
        else:
            cur.close()
            print(row)
            return 1

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
        return None
    
    
#====================================================================================================
def terminate():
    if conn is not None:
        conn.close()
   
