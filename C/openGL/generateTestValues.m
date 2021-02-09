% alimentacao, vestuario, deslocacoes, lazer, outros

%% FICHEIRO VAI FICAR ASSIM: Nome, Orcamento, Alimentacao no dia X, vestuario no dia X, .......
ValorMinimoAlimentacao = 20; 
ValorMaximoAlimentacao = 120;
ValorMinimoVestuario = 0;
ValorMaximoVestuario = 200;
ValorMinimoDeslocacoes=0;
ValorMaximoDeslocacoes=200;
ValorMinimoLazer=0;
ValorMaximoLazer=200;
ValorMinimoOutros=0;
ValorMaximoOutros=50;
alimentacaoDiaN=[];
vestuarioDiaN=[];
deslocacoesDiaN=[];
lazerDiaN=[];
outrosDiaN=[];
Ficheiro=[];
numeroDias=3650; % 10 anos

for K=1:numeroDias
alimentacaoDiaN = [alimentacaoDiaN; int32(ValorMinimoAlimentacao + (ValorMaximoAlimentacao-ValorMinimoAlimentacao).*rand(1,1))];
vestuarioDiaN = [vestuarioDiaN; int32(ValorMinimoVestuario + (ValorMaximoVestuario-ValorMinimoVestuario).*rand(1,1))];
deslocacoesDiaN = [deslocacoesDiaN; int32(ValorMinimoDeslocacoes + (ValorMaximoDeslocacoes-ValorMinimoDeslocacoes).*rand(1,1))];
lazerDiaN = [lazerDiaN; int32(ValorMinimoLazer + (ValorMaximoLazer-ValorMinimoLazer).*rand(1,1))];
outrosDiaN = [outrosDiaN; int32(ValorMinimoOutros + (ValorMaximoOutros-ValorMinimoOutros).*rand(1,1))];
end

orcamento= 10000;
fid=fopen('DadosOrcamento.txt','w');
fprintf(fid, ' %f ', orcamento);
fclose(fid);

dlmwrite('DadosAlimentacao.txt',alimentacaoDiaN,'delimiter',' ');
dlmwrite('DadosVestuario.txt',vestuarioDiaN,'delimiter',' ');
dlmwrite('DadosDeslocacoes.txt',deslocacoesDiaN,'delimiter',' ');
dlmwrite('DadosLazer.txt',lazerDiaN,'delimiter',' ');
dlmwrite('DadosOutros.txt',outrosDiaN,'delimiter',' ');

