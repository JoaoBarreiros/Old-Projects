#!/usr/bin/python
# -*- coding: latin-1 -*-


''' 
Modulo da Applicacao
=============

Este modulo faz de interface com o utilizador, apresenta os menus, pede dados, 
executa os comandos e apresenta os resultados.
'''

import menus, api, datetime, hashlib
#====================================================================================================
def encrypt(password):
    h = hashlib.md5(password.encode())
    return(h.hexdigest())
    
#====================================================================================================
def validate_option(op, max_op, min_op = 0):
    # valida se a op ÃƒÂ© um valor inteiro, e se se encontra entre min e max, inclusive
    
    try:
        op = int(op)
        if op >= min_op and op <= max_op:
            return op
    except:
        pass

    print('Valor incorreto, introduza um numero entre %d e %d' % (min_op, max_op))
    return -1
#====================================================================================================
def validate_date(date_text,mode):
    try:
        now = datetime.datetime.now()
        aux = datetime.datetime.strptime(date_text, '%Y-%m-%d')
        if aux.year >= 1900 and aux.year <= now.year or mode == 1:
            return 0
        else:
            print("A data de nascimento tem que estar entre 1900 e o ano atual")
            return -1
    except ValueError:
        try:
            aux = datetime.datetime.strptime(date_text, '%Y/%m/%d')
            if aux.year >= 1900 and aux.year <= now.year or mode == 1:
                return 0
            else:
                print("A data de nascimento tem que estar entre 1900 e o ano atual")
                return -1      
        except ValueError:
            try:
                aux = datetime.datetime.strptime(date_text, '%d/%m/%Y')
                if aux.year >= 1900 and aux.year <= now.year or mode == 1:
                    return 0
                else:
                    print("A data de nascimento tem que estar entre 1900 e o ano atual")
                    return -1
            except ValueError:
                try:
                    aux = datetime.datetime.strptime(date_text, '%d-%m-%Y')
                    if aux.year >= 1900 and aux.year <= now.year or mode == 1:
                        return 0
                    else:
                        print("A data de nascimento tem que estar entre 1900 e o ano atual")
                        return -1
                except ValueError:
                    print("Formato de data incorreto, deverá ser YYYY-MM-DD ou YYYY/MM/DD ou DD-MM-YYYY ou DD/MM/YYYY")
                    return -1
#====================================================================================================                
def apresentar_menu(menu_txt, max_op, min_op = 0):
    # mostra o menu atÃƒÂ© a opÃƒÂ§ÃƒÂ£o introduzida ser vÃƒÂ¡lida

    print(menu_txt)

    op = -1
    while op < 0:
        
        op = validate_option( input("Introduza a sua opção: "), max_op )

    return op
#====================================================================================================
def menu_user(username):
    # menu do utilizador normal

    menu_txt = menus.user
    while True:
        op = apresentar_menu(menu_txt, 5)

        if op == 1:
            menu_txt = menus.musica
            while True:
                op2 = apresentar_menu(menu_txt, 10)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 5:
                    if(validate_option(opcao, 100)>=0):
                        num,ID = api.mostramusica(int(opcao),op2)
                elif op2 == 6:
                    if(validate_date(opcao,1) == 0):
                        num,ID = api.mostramusica(opcao,op2) 
                else:
                    num,ID = api.mostramusica(opcao,op2)
                if num == 1:
                    menu_txt = menus.criticamusica
                    while True:
                        op3 = apresentar_menu(menu_txt, 3)
                        if op3 == 0:
                            menu_txt = menus.user
                            break
                        if op3 == 1:
                            
                            #vÃª critica da musica da pesquisa
                            if(api.existecritica(ID,op)):
                                api.mostracritica(ID,op)
                            else:
                                print('Não existem críticas')
                        if op3 == 2:
                            #insere crÃ­tica na mÃºsica da pesquisa
                            
                            texto = ''
                            while(texto == ''):
                                texto = input('Introduza a crítica: ')

                            isnumber = 0
                            while(isnumber == 0):
                                pontuacao = input('Introduza a pontuação de 0 a 100: ')
                                try:
                                    pontuacao  = int(pontuacao)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                                
                            if(validate_option(pontuacao,100) >= 0):
                                api.inserecriticamusica(ID,texto,pontuacao,username)
                        if op3 == 3:
                            isnumber = 0
                            while(isnumber == 0):
                                playlistid = input('Introduza o ID da playlist a qual deseja adicionar a música: ')
                                try:
                                    playlistid  = int(playlistid)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                                    
                        api.modifica_playlist2(ID, playlistid)
        elif op == 2:
             menu_txt = menus.album
             while True:
                op2 = apresentar_menu(menu_txt, 5)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 1:
                    if(validate_option(opcao, 100)>=0):
                        num,ID = api.mostraalbum(op2,int(opcao))
                elif op2 == 4:
                    if(validate_date(opcao,1) == 0):
                        num,ID = api.mostraalbum(op2,opcao)  
                else:
                    num,ID = api.mostraalbum(opcao,op2)
                if num == 1:
                    menu_txt = menus.criticaalbum
                    while True:
                        op3 = apresentar_menu(menu_txt, 2)
                        if op3 == 0:
                            menu_txt = menus.user
                            break
                        if op3 == 1:
                            #vÃª critica do Ã¡lbum da pesquisa
                            if(api.existecritica(ID,op)):
                                api.mostracritica(ID,op)    
                        if op3 == 2:
                            #insere crÃ­tica no Ã¡lbum da pesquisa
                            #not null
                            texto = ''
                            while(texto == ''):
                                texto = input('Introduza a crítica: ')

                            isnumber = 0
                            while(isnumber == 0):
                                pontuacao = input('Introduza a pontuação de 0 a 100: ')
                                try:
                                    pontuacao  = int(pontuacao)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                                
                            if(validate_option(pontuacao,100) >= 0):
                                api.inserecriticaalbum(ID,texto,pontuacao,username)
                                        
        elif op == 3:
             menu_txt = menus.autor
             while True:
                op2 = apresentar_menu(menu_txt, 6)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 6:
                    if(validate_date(opcao,1) == 0):
                        api.mostraautor(opcao,6)      
                else:
                    api.mostraautor(opcao,op2)
                    
        elif op == 4:
            #Gerir playlist
            menu_txt = menus.gereplaylist
            while True:
                op2 = apresentar_menu(menu_txt, 4)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                elif op2 == 1:
                #insere playlist
                    
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir na playlist: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir no álbum: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                         
                    nomeplaylist = ''
                    while(nomeplaylist == ''):
                        nomeplaylist = input('Introduza o nome da playlist:' )
                        
                    tipoplaylist = 0
                    tipoplaylist = input('Introduza o tipo da playlist (0 - Privada, 1 - Pública): ')
                            
                    api.inserir_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist, username)
                elif op2 == 2:
                    #modifica playlist
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir na playlist: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir na playlist: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                         
                    nomeplaylist = ''
                    while(nomeplaylist == ''):
                        nomeplaylist = input('Introduza o nome da playlist:' )
                        
                    tipoplaylist = 0
                    tipoplaylist = input('Introduza o tipo da playlist (0 - Privada, 1 - Pública): ')
                    
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist: ')
                        try:
                            playlistid  = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeplaylist(playlistid):
                        api.modifica_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist,playlistid)
                        
                elif op2 == 3:
                #remove playlist
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist: ')
                        try:
                            playlistid = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeplaylist(playlistid):
                        api.remove_playlist(playlistid)
                    
                elif op2 == 4:
                #procura playlist
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist que pretende procurar: ')
                        try:
                            playlistid = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeplaylist(playlistid):
                        api.mostraplaylist(playlistid)
                    
        elif op == 5:
            menu_txt = menus.partilha
            while True:
                op2 = apresentar_menu(menu_txt, 2)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                if op2 == 1:
                #Partilhado comigo
                    api.mostrarpartilha(username)
                if op2 == 2:
                #Partilhar
                    nomeutilizador = ''
                    while(nomeutilizador == ''):
                        nomeutilizador = input('Introduza o nome do utilizar com quem quer partilhar: ')
                        
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer partilhar: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende partilhar: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1

                    api.inserirpartilha(nomeutilizador,numeromusicas,musicaid)
                        
        elif op == 0:
            break
#====================================================================================================
def criar_autor():
    nome = ''
    while(nome == ''):
        nome = input('Introduza o nome do autor:' )
    biografia = input('Introduza a biografia do autor:' )
    nacionalidade = input('Introduza a nacionalidade do autor:' )
    paginaWeb = input('Introduza a página web do autor:' )
    aux = -1
    while aux == -1:
        dataInicio = input('Introduza a data de inicio de carreira do autor:' )
        aux = validate_date(dataInicio,1)
    aux = -1
    while aux == -1:
        dataFim = input('Introduza a data de fim de carreira do autor(se houver):' )
        aux = validate_date(dataInicio,1)
    if biografia == '':
        biografia = None
    if dataFim == '':
        dataFim = None
    if nacionalidade == '':
        nacionalidade = None
    if paginaWeb == '':
        pagineWeb = None
    return api.inserir_autor(biografia,nacionalidade,dataInicio,paginaWeb,nome,dataFim)
#====================================================================================================
def modifica_autor():
    isnumber = 0
    while(isnumber == 0):
        autorid = input('Introduza o ID do autor: ')
        try:
            autorid = int(autorid)
            isnumber = 1
        except:
            isnumber = 0
    nome = ''
    while(nome == ''):
        nome = input('Introduza o nome do autor:' )
    biografia = input('Introduza a biografia do autor:' )
    nacionalidade = input('Introduza a nacionalidade do autor:' )
    paginaWeb = input('Introduza a pagina web do autor:' )
    aux = -1
    while aux == -1:
        dataInicio = input('Introduza a data de inicio de carreira do autor:' )
        aux = validate_date(dataInicio,1)
    aux = -1
    while aux == -1:
        dataFim = input('Introduza a data de fim de carreira do autor(se houver):' )
        aux = validate_date(dataInicio,1)
    if biografia == '':
        biografia = None
    if dataFim == '':
        dataFim = None
    if nacionalidade == '':
        nacionalidade = None
    if paginaWeb == '':
        pagineWeb = None

    if existeautor(autorid):  
        api.modifica_autor(autorid,biografia,nacionalidade,dataInicio,paginaWeb,nome,dataFim)
    return autorid
#====================================================================================================
def menu_editor(username):
    # menu do editor

    menu_txt = menus.editor
    while True:
        op = apresentar_menu(menu_txt, 11)

        if op == 1:
            #procurar musica
            menu_txt = menus.musica
            while True:
                op2 = apresentar_menu(menu_txt, 10)
                if op2 == 0:
                    #sair
                    menu_txt = menus.editor
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 5:
                    if(validate_option(opcao, 100)>=0):
                        num,ID = api.mostramusica(int(opcao),op2)
                elif op2 == 6:
                    if(validate_date(opcao,1) == 0):
                        num,ID = api.mostramusica(opcao,op2)
                else:
                    num,ID = api.mostramusica(opcao,op2)
                if num == 1:
                    menu_txt = menus.criticamusica
                    while True:
                        op3 = apresentar_menu(menu_txt, 3)
                        if op3 == 0:
                            menu_txt = menus.editor
                            break
                        if op3 == 1:
                            #vÃª critica da musica da pesquisa
                            if(api.existecritica(ID,op)):
                                api.mostracritica(ID,op)    
                        if op3 == 2:
                            #insere crÃ­tica na mÃºsica da pesquisa
                            texto = ''
                            while(texto == ''):
                                texto = input('Introduza a crítica: ')

                            isnumber = 0
                            while(isnumber == 0):
                                pontuacao = input('Introduza a pontuação de 0 a 100: ')
                                try:
                                    pontuacao  = int(pontuacao)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                                
                            if(validate_option(pontuacao,100) >= 0):
                                api.inserecriticamusica(ID,texto,pontuacao,username)
                        if op3 == 3:
                            isnumber = 0
                            while(isnumber == 0):
                                playlistid = input('Introduza o ID da playlist a qual deseja adicionar a música: ')
                                try:
                                    playlistid  = int(playlistid)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                        api.modifica_playlist2(ID, playlistid)
                        
        elif op == 2:
             menu_txt = menus.album
             while True:
                op2 = apresentar_menu(menu_txt, 5)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 1:
                    if(validate_option(opcao, 100)>=0):
                        num,ID = api.mostraalbum(op2,int(opcao))
                elif op2 == 4:
                    if(validate_date(opcao,1) == 0):
                        num,ID = api.mostraalbum(op2,opcao)  
                else:
                    num,ID = api.mostraalbum(opcao,op2)
                if num == 1:
                    menu_txt = menus.criticaalbum
                    while True:
                        op3 = apresentar_menu(menu_txt, 2)
                        if op3 == 0:
                            menu_txt = menus.editor
                            break
                        if op3 == 1:
                            #vÃª critica do Ã¡lbum da pesquisa
                            if(api.existecritica(ID,op)):
                                api.mostracritica(ID,op)    
                        if op3 == 2:
                            #insere crÃ­tica no Ã¡lbum da pesquisa

                            texto = ''
                            while(texto == ''):
                                texto = input('Introduza a crítica: ')

                            isnumber = 0
                            while(isnumber == 0):
                                pontuacao = input('Introduza a pontuação de 0 a 100: ')
                                try:
                                    pontuacao  = int(pontuacao)
                                    isnumber = 1
                                except:
                                    isnumber = 0
                                
                            if(validate_option(pontuacao,100) >= 0):
                                api.inserecriticaalbum(ID,texto,pontuacao,username)

                            
        elif op == 3:
             menu_txt = menus.autor
             while True:
                op2 = apresentar_menu(menu_txt, 6)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                opcao = input('Introduza a sua pesquisa: ')
                if op2 == 6:
                    if(validate_date(opcao,1) == 0):
                        api.mostraautor(opcao,6)      
                else:
                    api.mostraautor(opcao,op2)
        elif op == 4:
            #Gerir playlist
            menu_txt = menus.gereplaylist
            while True:
                op2 = apresentar_menu(menu_txt, 4)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                elif op2 == 1:
                #insere playlist
                    
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir na playlist: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir no álbum: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                         
                    nomeplaylist = ''
                    while(nomeplaylist == ''):
                        nomeplaylist = input('Introduza o nome da playlist:' )
                        
                    tipoplaylist = 0
                    tipoplaylist = input('Introduza o tipo da playlist (0 - Privada, 1 - Pública): ')
                            
                    api.inserir_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist, username)
                elif op2 == 2:
                    #modifica playlist
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir na playlist: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir na playlist: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                         
                    nomeplaylist = ''
                    while(nomeplaylist == ''):
                        nomeplaylist = input('Introduza o nome da playlist:' )
                        
                    tipoplaylist = 0
                    tipoplaylist = input('Introduza o tipo da playlist (0 - Privada, 1 - Pública): ')
                    
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist: ')
                        try:
                            playlistid  = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeplaylist(playlistid):
                        api.modifica_playlist(musicaid, numeromusicas, nomeplaylist,tipoplaylist,playlistid)
                elif op2 == 3:
                #remove playlist
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist: ')
                        try:
                            playlistid = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                    if api.existeplaylist(playlistid):
                        api.remove_playlist(playlistid)
                elif op2 == 4:
                #procura playlist
                    isnumber = 0
                    while(isnumber == 0):
                        playlistid = input('Introduza o ID playlist que pretende procurar: ')
                        try:
                            playlistid = int(playlistid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeplaylist(playlistid):
                        api.mostraplaylist(playlistid)
        elif op == 5:
            menu_txt = menus.geremusica
            while True:
                op2 = apresentar_menu(menu_txt, 3)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                elif op2 == 1:
                #insere mÃºsica
                    
                    nomemusica = ''
                    while(nomemusica == ''):
                        nomemusica = input('Introduza o nome da música: ')
                        
                    aux = -1
                    while aux == -1:
                        datalancamento = input('Introduza a data de lançamento da música: ')
                        aux = validate_date(datalancamento,1)
                
                    informacoes = input('Introduza as informações da música: ')
                    if informacoes == '':
                        informacoes = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        duracao = input('Introduza a duração da música: ')
                        try:
                            duracao = float(duracao)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    letra= input('Introduza a letra da música: ')
                    if letra == '':
                        letra = None
                        
                    estudiogravacao = ''
                    while(estudiogravacao == ''):
                        estudiogravacao = input('Introduza o estúdio de gravação da música: ')
                    
                    ficheiro_nomeficheiro = ''
                    while(ficheiro_nomeficheiro == ''):
                        ficheiro_nomeficheiro = input('Introduza o nome do ficheiro da música: ')

                    isnumber = 0
                    while(isnumber == 0):
                        ficheiro_tamanhoficheiro = input('Introduza o tamanho do ficheiro a música: ')
                        try:
                            ficheiro_tamanhoficheiro = int(ficheiro_tamanhoficheiro)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    ficheiro_tipoficheiro = ''
                    while(ficheiro_tipoficheiro == ''):
                        ficheiro_tipoficheiro = input('Introduza o tipo de ficheiro: ')
                    
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                        
                    genero = ''
                    while(genero == ''):
                         genero = input('Introduza o género da música: ')

                    #concerto
                    
                    if api.existeautor(autorid) and api.existegenero(genero):
                        api.inseremusica(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autorid,genero,username)
                elif op2 == 2:
                    
                    #modificar mÃºsica
                    nomemusica = ''
                    while(nomemusica == ''):
                        nomemusica = input('Introduza o nome da música: ')
                        
                    aux = -1
                    while aux == -1:
                        datalancamento = input('Introduza a data de lançamento da música: ')
                        aux = validate_date(datalancamento,1)
                
                    informacoes = input('Introduza as informações da música: ')
                    if informacoes == '':
                        informacoes = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        duracao = input('Introduza a duração da música: ')
                        try:
                            duracao = float(duracao)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    letra= input('Introduza a letra da música: ')
                    if letra == '':
                        letra = None
                        
                    estudiogravacao = ''
                    while(estudiogravacao == ''):
                        estudiogravacao = input('Introduza o estúdio de gravação da música: ')
                    
                    ficheiro_nomeficheiro = ''
                    while(ficheiro_nomeficheiro == ''):
                        ficheiro_nomeficheiro = input('Introduza o nome do ficheiro da música: ')

                    isnumber = 0
                    while(isnumber == 0):
                        ficheiro_tamanhoficheiro = input('Introduza o tamanho do ficheiro a música: ')
                        try:
                            ficheiro_tamanhoficheiro = int(ficheiro_tamanhoficheiro)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    ficheiro_tipoficheiro = ''
                    while(ficheiro_tipoficheiro == ''):
                        ficheiro_tipoficheiro = input('Introduza o tipo de ficheiro: ')
                    
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                        
                    genero = ''
                    while(genero == ''):
                         genero = input('Introduza o género da música: ')
                         
                    isnumber = 0
                    while(isnumber == 0):
                        musicaid = input('Introduza o ID da música: ')
                        try:
                            musicaid = int(musicaid)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    if api.existeautor(autorid) and api.existegenero(genero) and api.existemusica(musicaid):
                        api.modificamusica(nomemusica,datalancamento,informacoes,duracao,letra,estudiogravacao,ficheiro_nomeficheiro,ficheiro_tamanhoficheiro,ficheiro_tipoficheiro,autorid,genero,musicaid)
                       

                elif op2 == 3:
                    #remover mÃºsica
                    isnumber = 0
                    while(isnumber == 0):
                        musicaid = input('Introduza o ID da música: ')
                        try:
                            musicaid = int(musicaid)
                            isnumber = 1
                        except:
                            isnumber = 0
                    if api.existemusica(musicaid):
                        api.removemusica(musicaid)
                    
        elif op == 6:
            #Gerir um Ã¡lbum
            menu_txt = menus.gerealbum
            while True:
                op2 = apresentar_menu(menu_txt, 3)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                elif op2 == 1:
                    #Adicionar álbum
                    
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir no álbum: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir no álbum: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                    aux = -1
                    while(aux == -1):
                        datacriacao = input('Introduza a data de criação do álbum: ')
                        aux = validate_date(datacriacao,1)
                         
                    nomealbum = ''
                    while(nomealbum == ''):
                        nomealbum = input('Introduza o nome do álbum:' )
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeautor(autorid):        
                        api.inserir_album(musicaid, numeromusicas, datacriacao, nomealbum, autorid)
                        
                elif op2 == 2:
                    #Modificar álbum
                    
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer introduzir no álbum: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende inserir no álbum: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                     
                    aux = -1
                    while(aux == -1):
                        datacriacao = input('Introduza a data de criação do álbum: ')
                        aux = validate_date(datacriacao,1)
                         
                    nomealbum = ''
                    while(nomealbum == ''):
                        nomealbum = input('Introduza o nome do álbum:' )
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    isnumber = 0
                    while(isnumber == 0):
                        albumid = input('Introduz o ID do álbum: ')
                        try:
                            albumid = int(albumid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if existealbum(albumid):      
                        api.modifica_album(musicaid, numeromusicas, datacriacao, nomealbum, autorid, albumid)
                        
                elif op2 == 3:
                    #Remove álbum
                    isnumber = 0
                    while(isnumber == 0):
                        albumid = input('Introduza o ID do álbum: ')
                        try:
                            albumid = int(albumid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if existealbum(albumid):    
                        api.remove_album(albumid)
        elif op == 7:
            #Gerir um autor
            menu_txt = menus.gereautor
            while True:
                op2 = apresentar_menu(menu_txt, 7)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                if op2 == 1:
                    #inserir artista
                    criar_autor()
                    aux = -1
                    while(aux == -1):
                        datanascimento = input('Introduza a data de nascimento do artista: ')
                        aux = validate_date(datanascimento,0)
                        
                    pseudonimo = input('Introduza o pseudónimo do artista(caso tenha): ')
                    if pseudonimo == '':
                        pseudonimo = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        ccartista = input('Introduza o CC do artista: ')
                        try:
                            ccartista = int(ccartista)
                            isnumber = 1
                        except:
                            isnumber = 0
                        
                    api.inserir_artista(datanascimento,pseudonimo,ccartista)
                    
                elif op2 == 2:
                    criar_autor()
                    
                    #inserir grupo musical
                    isnumber = 0
                    while(isnumber == 0):
                        numeromembros = input('Introduza o número de membros do grupo: ')
                        try:
                            numeromembros = int(numeromembros)
                            isnumber = 1
                        except:
                            isnumber = 0
   
                    api.inserir_grupomusical(numeromembros)
                    
                elif op2 == 3:
                    #inserir compositor
                    criar_autor()

                    isnumber = 0
                    while(isnumber == 0):
                        cccompositor = input('Introduza o CC do compositor: ')
                        try:
                            cccompositor = int(cccompositor)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    nomecompositor = ''
                    while(nomecompositor == ''):
                        nomecompositor = input('Introduza o nome do compositor: ')

                    aux = -1
                    while(aux == -1):
                        datainicial = input('Introduza a data incial de carreira do compositor: ')
                        aux = validate_date(dataincial,1)
                    
                        
                    datafinal = input('Introduza a data final de carreira do compositor(se houver): ')
                    if datafinal == '':
                        datafinal = None
                        
                    aux = -1
                    while(aux == -1):
                         datanascimento = input('Introduza a data de nascimento do compositor: ')
                         aux = validate_date(datanascimento,0)
 
                    api.insere_compositor(ccompositor,nomecompositor,dataincial,datafinal,datanascimento)
                
                elif op2 == 4:
                    #modificar artista
                    autorid = modifica_autor()
                    
                    aux = -1
                    while(aux == -1):
                        datanascimento = input('Introduza a data de nascimento do artista: ')
                        aux = validate_date(datanascimento,0)
                        
                    pseudonimo = input('Introduza o pseudonimo do artista(caso tenha): ')
                    if pseudonimo == '':
                        pseudonimo = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        ccartista = input('Introduza o CC do artista: ')
                        try:
                            ccartista = int(ccartista)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
        
                    api.modifica_artista(datanascimento,pseudonimo,ccartista,autorid)
                elif op2 == 5:
                    #modificar grupo musical
                    autorid = modifica_autor()
                    
                    isnumber = 0
                    while(isnumber == 0):
                        numeromembros = input('Introduza o número de membros do grupo: ')
                        try:
                            numeromembros = int(numeromembros)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    api.modifica_grupomusical(numeromembros,autorid)
                elif op2 == 6:
                    #modificar compositor
                    autorid = modifica_autor()
                    
                    isnumber = 0
                    while(isnumber == 0):
                        cccompositor = input('Introduza o CC do compositor: ')
                        try:
                            cccompositor = int(cccompositor)
                            isnumber = 1
                        except:
                            isnumber = 0
                    
                    nomecompositor = ''
                    while(nomecompositor == ''):
                        nomecompositor = input('Introduza o nome do compositor: ')

                    aux = -1
                    while(aux == -1):
                        datainicial = input('Introduza a data incial de carreira do compositor: ')
                        aux = validate_date(dataincial,1)
                    
                    datafinal = input('Introduza a data final de carreira do compositor(se houver): ')
                    if datafinal == '':
                        datafinal = None    
                    
                    
                    aux = -1
                    while(aux == -1):
                         datanascimento = input('Introduza a data de nascimento do compositor: ')
                         aux = validate_date(datanascimento,0)
                         
                    api.modifica_compositor(cccompositor,nomecompositor,dataincial,datafinal,datanascimento,autorid)
                elif op2 == 7:
                    #remover autor
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    if api.existeautor(autorid):
                        api.remove_autor(autorid)
        elif op == 8:
            #Gerir um utilizador
            menu_txt = menus.gereutilizador
            while True:
                op2 = apresentar_menu(menu_txt, 3)
                if op2 == 0:
                    menu_txt = menus.editor
                    break
                if op2 == 1:
                #Insere utilizador
                    
                    nomeutilizador = ''
                    while(nomeutilizador == ''):
                        nomeutilizador = input('Introduza o nome do utilizador: ')
                        
                    palavrapasse = ''
                    while(palavrapasse == ''):
                        palavrapasse = input('Introduza a palavra passe do utilizador: ')
                        
                    tipoutilizador = 0
                    tipoutilizador = input('Introduza o tipo da utilizador (0 - Utilizador normal, 1 - Editor): ')
                    
                    email = ''
                    while(email == ''):
                        email = input('Introduza o email do utilizador: ')
                        
                    valdate = -1
                    while valdate < 0:
                        datanascimento = input('Introduza a data de nascimento do utilizador: ')
                        valdate = validate_date(datanascimento,0)
                        
                    primeironome = input('Intorudza o primeiro nome do utilizador: ')
                    if primeironome == '':
                        primeironome = None
                    
                    ultimonome = input('Intorudza o último nome do utilizador: ')
                    if ultimonome == '':
                        ultimonome = None
                        
                    pais = input('Introduza o país do utilizador: ')
                    if pais == '':
                        pais = None
                        
                    genero = input('Introduza o género do utilizador: ')
                    if genero == '':
                        genero = None
                        
                    api.insereutilizador(nomeutilizador,encrypt(palavrapasse),tipoutilizador,email,datanascimento,primeironome,ultimonome,pais,genero)
                    
                if op2 == 2:
                #Modifica utilizador
                    
                    nomeutilizador = ''
                    while(nomeutilizador == ''):
                        nomeutilizador = input('Introduza o nome do utilizador: ')
                        
                    palavrapasse = ''
                    while(palavrapasse == ''):
                        palavrapasse = input('Introduza a palavra passe do utilizador: ')
                        
                    tipoutilizador = 0
                    tipoutilizador = input('Introduza o tipo da utilizador (0 - Utilizador normal, 1 - Editor): ')
                    
                    email = ''
                    while(email == ''):
                        email = input('Introduza o email do utilizador: ')
                        
                    valdate = -1
                    while valdate < 0:
                        datanascimento = input('Introduza a data de nascimento do utilizador: ')
                        valdate = validate_date(datanascimento,0)
                        
                    primeironome = input('Intorudza o primeiro nome do utilizador: ')
                    if primeironome == '':
                        primeironome = None
                    
                    ultimonome = input('Intorudza o último nome do utilizador: ')
                    if ultimonome == '':
                        ultimonome = None
                        
                    pais = input('Introduza o país do utilizador: ')
                    if pais == '':
                        pais = None
                        
                    genero = input('Introduza o género do utilizador: ')
                    if genero == '':
                        genero = None
                        
                    if api.existeutilizador(email):
                        api.modificautilizador(nomeutilizador,encrypt(palavrapasse),tipoutilizador,email,datanascimento,primeironome,ultimonome,pais,genero)
                        
                if op2 == 3:
                #Remove utilizador
                    email = ''
                    while(email == ''):
                        email = input('Introduza o email do utilizador: ')
                        
                    if api.existeutilizador(email):
                        api.removeutilizador(email)
        elif op == 9:
            #Gerir um concerto
            menu_txt = menus.gereconcerto
            while True:
                op2 = apresentar_menu(menu_txt, 3)
                if op2 == 0:
                    #sair
                    menu_txt = menus.editor
                    break
                if op2 == 1:
                #Insere concerto
                    
                    localidade = ''
                    while(localidade == ''):
                        localidade = input('Introduza a localidade do concerto: ')
                        
                    valdate = -1
                    while valdate < 0:
                        data = input('Introduza a data do concerto: ')
                        valdate = validate_date(data,1)
                        
                    nomeconcerto = input('Introduza o nome do concerto: ')
                    if nomeconcerto == '':
                        nomeconcerto = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        lotacao = input('Introduza a lotação do concerto: ')
                        try:
                            lotacao = int(lotacao)
                            isnumber = 1
                        except:
                            isnumber = 0    
                    
                    isnumber = 0
                    while(isnumber == 0):
                        precobilhete = input('Introduza o preço do bilhete do concerto(em euros): ')
                        try:
                            precobilhete = float(precobilhete)
                            isnumber = 1
                        except:
                            isnumber = 0 
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor que atua no concerto: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que foram tocadas no concerto: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que foram tocadas no concerto ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                        
                    if api.existeautor(autorid):    
                        api.insereconcerto(localidade,data,nomeconcerto,lotacao,precobilhete,autorid,numeromusicas,musicaid)
                        
                if op2 == 2:
                #Modificar concerto
                    
                    localidade = ''
                    while(localidade == ''):
                        localidade = input('Introduza a localidade do concerto: ')
                        
                    valdate = -1
                    while valdate < 0:
                        data = input('Introduza a data do concerto: ')
                        valdate = validate_date(data,1)
                        
                    nomeconcerto = input('Introduza o nome do concerto: ')
                    if nomeconcerto == '':
                        nomeconcerto = None
                        
                    isnumber = 0
                    while(isnumber == 0):
                        lotacao = input('Introduza a lotação do concerto: ')
                        try:
                            lotacao = int(lotacao)
                            isnumber = 1
                        except:
                            isnumber = 0    
                    
                    isnumber = 0
                    while(isnumber == 0):
                        precobilhete = input('Introduza o preço do bilhete do concerto(em euros): ')
                        try:
                            precobilhete = float(precobilhete)
                            isnumber = 1
                        except:
                            isnumber = 0 
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor que atua no concerto: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que foram tocadas no concerto: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que foram tocadas no concerto ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1
                        
                    if api.existeconcerto(localidade,data):    
                        api.modificaconcerto(localidade,data,nomeconcerto,lotacao,precobilhete,autorid,numeromusicas,musicaid)
                        
                if op2 == 3:
                #Remove concerto
                    
                    localidade = ''
                    while(localidade == ''):
                        localidade = input('Introduza a localidade do concerto: ')
                        
                    valdate = -1
                    while valdate < 0:
                        data = input('Introduza a data do concerto: ')
                        valdate = validate_date(data,1)
                        
                    if api.existeconcerto(localidade,data):    
                        api.removeconcerto(localidade,data)
        if op == 10:
            #Gerir editoras
            menu_txt = menus.gereeditora
            while True:
                op2 = apresentar_menu(menu_txt, 3)
                if op2 == 0:
                    #sair
                    menu_txt = menus.editor
                    break
                if op2 == 1:
                #Insere editora
                    
                    editoranome = ''
                    while(editoranome == ''):
                        editoranome = input('Introduza o nome da editora: ')
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor que está associado à editora introduzida: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    valdate = -1
                    while valdate < 0:
                        datafundacao = input('Introduza a data de fundacao da editora: ')
                        valdate = validate_date(datafundacao,1)
                        
                    valdate = -1
                    while valdate < 0:
                        datainicio = input('Introduza a data em que o autor assinou o contrato com a editora introduzida: ')
                        valdate = validate_date(datainicio,0)

                    valdate = -1
                    while valdate < 0:
                        datafim = input('Introduza a data em que o autor terminou o contrato com a editora introduzida: ')
                        valdate = validate_date(datafim,0)
                        
                        
                    if api.existeautor(autorid) and api.existeeditora(editoranome,datafundacao):    
                        api.insereeditora(editoranome,autorid,datafundacao,datainicio,datafim)
                if op2 == 2:
                #Modifica editora
                    
                        editoranome = ''
                        while(editoranome == ''):
                            editoranome = input('Introduza o nome da editora: ')
                            
                        isnumber = 0
                        while(isnumber == 0):
                            autorid = input('Introduza o ID do autor que está associado à editora introduzida: ')
                            try:
                                autorid = int(autorid)
                                isnumber = 1
                            except:
                                isnumber = 0
                                
                        valdate = -1
                        while valdate < 0:
                            datafundacao = input('Introduza a data de fundacao da editora: ')
                            valdate = validate_date(datafundacao,1)
                            
                        valdate = -1
                        while valdate < 0:
                            datainicio = input('Introduza a data em que o autor assinou o contrato com a editora introduzida: ')
                            valdate = validate_date(datainicio,0)

                        valdate = -1
                        while valdate < 0:
                            datafim = input('Introduza a data em que o autor terminou o contrato com a editora introduzida: ')
                            valdate = validate_date(datafim,0)
                            
                            
                        if api.existeautor(autorid) and api.existeeditora(editoranome,datafundacao):    
                            api.modificaeditora(editoranome,autorid,datafundacao,datainicio,datafim)
                        
                if op2 == 3:
                #Remove concerto
                    
                    editoranome = ''
                    while(editoranome == ''):
                        editoranome = input('Introduza o nome da editora: ')
                        
                    isnumber = 0
                    while(isnumber == 0):
                        autorid = input('Introduza o ID do autor que está associado à editora introduzida: ')
                        try:
                            autorid = int(autorid)
                            isnumber = 1
                        except:
                            isnumber = 0
                            
                    valdate = -1
                    while valdate < 0:
                        datafundacao = input('Introduza a data de fundacao da editora: ')
                        valdate = validate_date(datafundacao,1)
                        
                    valdate = -1
                    while valdate < 0:
                        datainicio = input('Introduza a data em que o autor assinou o contrato com a editora introduzida: ')
                        valdate = validate_date(datainicio,0)

                    valdate = -1
                    while valdate < 0:
                        datafim = input('Introduza a data em que o autor terminou o contrato com a editora introduzida: ')
                        valdate = validate_date(datafim,0)
                        
                    if api.existeautor(autorid) and api.existeeditora(editoranome,datafundacao):    
                        api.removeeditora(editoranome,autorid,datafundacao,datainicio,datafim)
                        
        if op == 11:
            menu_txt = menus.partilha
            while True:
                op2 = apresentar_menu(menu_txt, 2)
                if op2 == 0:
                    menu_txt = menus.user
                    break
                if op2 == 1:
                #Partilhado comigo
                    api.mostrarpartilha(username)
                if op2 == 2:
                #Partilhar
                    nomeutilizador = ''
                    while(nomeutilizador == ''):
                        nomeutilizador = input('Introduza o nome do utilizar com quem quer partilhar: ')
                        
                    isnumber = 0
                    while(isnumber == 0):
                        numeromusicas = input('Introduza o número de músicas que quer partilhar: ')
                        try:
                            numeromusicas  = int(numeromusicas)
                            isnumber = 1
                        except:
                            isnumber = 0
                 
                    musicaid = [None]*numeromusicas
                    
                    i = 0
                    while(i < numeromusicas):
                        aux = 0
                        while(aux == 0):
                            isnumber = 0
                            while(isnumber == 0):
                                musicaid[i] = input('Introduza o ID da música que pretende partilhar: ')
                                try:
                                    musicaid[i]  = int(musicaid[i])
                                    isnumber = 1
                                except:
                                    isnumber = 0
                            if api.existemusica(musicaid[i]):
                               aux = 1
                        i = i + 1

                    api.inserirpartilha(nomeutilizador,numeromusicas,musicaid)
                    
        elif op == 0:
            break
#====================================================================================================
def menu_login():
    # menu de login

    # pedir username e password ao utilizador
    username = ''
    while(username == ''):
        username = input('Username: ')
        
    password = ''
    while(password == ''):
        password = input('Password: ')

    # chamar a api para ir validar o username e password ÃƒÂ  base de dados
    user = api.login(username, encrypt(password))
    if not user == None:
        print('Login efectuado com sucesso!')
        input('Pressione enter para continuar...')
        # apresentamos um menu diferente em funcao do tipo de utilizador
        if user['tipo'] == False:
            menu_user(username)
        elif user['tipo'] == True:
            menu_editor(username)
        
    else:
        print('Username ou password inválidos, tente novamente')

#====================================================================================================
def menu_registo():
    # menu de registo

    username = ''
    while(username == ''):
        username = input('Username: ')
        
    password = ''
    while(password == ''):
        password = input('Password: ')
    
    valdate = -1
    while valdate < 0:
        datanascimento = input('Data de Nascimento: ')
        valdate = validate_date(datanascimento,0)
        
    email = ''
    while(email == ''):
        email = input('Email: ')
        
    primeironome = input('Primeiro Nome: ')
    if primeironome == '':
        primeironome = None
        
    ultimonome = input('Último Nome: ')
    if ultimonome == '':
        ultimonome = None
    
    pais = input('País: ')
    if pais == '':
        pais = None
        
    genero = input('Género: ')
    if genero == '':
        genero = None
        
    user = api.registo(username,encrypt(password),email,datanascimento,primeironome,ultimonome,pais,genero)
    if not user == None:
        print('Registo efectuado com sucesso!')
        input('Pressione enter para continuar...')
        # apresentamos um menu diferente em funcao do tipo de utilizador
        if user['tipo'] == False:
            menu_user(username)
        elif user['tipo'] == True:
            menu_editor(username)
        
    else:
        print('Username ou email já existentes, tente novamente')
#====================================================================================================
def menu_inicial():
    # menu inicial

    menu_txt = menus.inicial

    while True:
        op = apresentar_menu(menu_txt, 2)

        if op == 1:
            menu_login()
        elif op == 2:
            menu_registo()
        else:
            print('Obrigado por usar o DropMusic. Adeus!')
            api.terminate()
            break
#====================================================================================================
if __name__ == '__main__':
    menu_inicial()


