function [ dadesUlls, f ] = obtenirCaracteristiquesUlls(ulls, f)
% ObtenirCaracteristiquesUlls Obté característiques importants de cada imatge.

    dadesUlls = struct();
    
    for i = 1 : length(ulls)
        waitbar(i/length(ulls), f, 'Analitzant ulls');
        ullActual = ulls{i};
        
        cropE = [ullActual.posUlls(1) - 20, ullActual.posUlls(2) - 20, 40, 40];
        ullE = imresize(imcrop(ullActual.imatge, cropE), [64, 64]);
        
        cropD = [ullActual.posUlls(3) - 20, ullActual.posUlls(4) - 20, 40, 40];
        ullD = imresize(imcrop(ullActual.imatge, cropD), [64, 64]);
        
        caractE = getFeatures(ullE);
        caractD = getFeatures(ullD);
        caractE.tipus = 'ull';
        caractD.tipus = 'ull';
        
        % Hem de fer aixo per donar forma al struct
        if i == 1
            dadesUlls = caractD;
        end
        
        dadesUlls(2*i) = caractD;
        dadesUlls(2*i-1) = caractE;
    end
end

