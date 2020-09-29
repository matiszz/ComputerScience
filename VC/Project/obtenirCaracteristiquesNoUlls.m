function [ dadesNoUlls, f ] = obtenirCaracteristiquesNoUlls(ulls, f)
% ObtenirCaracteristiquesNoUlls Obté característiques importants de cada imatge.
    
    dadesNoUlls = struct();
    
    for i = 1 : length(ulls)
        waitbar(i/length(ulls), f, 'Analitzant No-ulls');
        numImgs = 9;
    
        for j = 1 : numImgs
            
            [sx, sy] = size(ulls{i}.imatge);
            x = randi(sx-40);
            y = randi(sy-40);
            
            % Retallem la imatge i generem features
            crop = [y, x, 40, 40];
            imatge = imresize(imcrop(ulls{i}.imatge, crop), [64, 64]);
            
            caracts = getFeatures(imatge);
            caracts.tipus = 'noUll';
            
            % Hem de fer aixo per donar forma al struct
            if and(i == 1, j == 1)
                dadesNoUlls = caracts;
            end
            
            dadesNoUlls(numImgs*(i-1)+j) = caracts;
            
        end
    end
end

