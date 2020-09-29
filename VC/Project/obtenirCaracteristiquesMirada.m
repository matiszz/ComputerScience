function [ dadesUllsNoMirant, f ] = obtenirCaracteristiquesMirada( ulls, f, label )
% ObtenirCaracteristiquesUllsNoMirant Obté característiques importants de cada imatge.

    dadesUllsNoMirant = struct();
    
    if label == "mirant"
        looking = 1;
    else
        looking = 0;
    end
    
    count = 1;
    for i = 1 : length(ulls)
        waitbar(i/length(ulls), f, 'Analitzant mirada');
        
        ullActual = ulls{i};
        if ullActual.mirant == looking
            cropE = [ullActual.posUlls(1) - 20, ullActual.posUlls(2) - 20, 40, 40];
            ullE = imresize(imcrop(ullActual.imatge, cropE), [64, 64]);

            cropD = [ullActual.posUlls(3) - 20, ullActual.posUlls(4) - 20, 40, 40];
            ullD = imresize(imcrop(ullActual.imatge, cropD), [64, 64]);

            caractE = getFeaturesLook(ullE);
            caractD = getFeaturesLook(ullD);
            caractE.tipus = label;
            caractD.tipus = label;

            % Hem de fer aixo per donar forma al struct
            if count == 1
                dadesUllsNoMirant = caractD;
            end

            dadesUllsNoMirant(2*count) = caractD;
            dadesUllsNoMirant(2*count-1) = caractE;
            count = count +1;
        end
    end
end
