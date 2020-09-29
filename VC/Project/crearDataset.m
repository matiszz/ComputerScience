function [caractUlls, caractNoUlls, entrenamentUll, testingUll] = crearDataset( ulls, f)
% CrearDataset crea un dataset de categories de ulls, no ulls, entrenament
% i testing.

    % Obtenim característiques dels ulls i dels no-ulls
    % Cada struct té unes característiques, i tipus, que pot ser ull o noUll
    [caractUlls, f] = obtenirCaracteristiquesUlls(ulls, f);
    [caractNoUlls, f] = obtenirCaracteristiquesNoUlls(ulls, f);

    % Ara hem de separar entre dades de testing i dades per entrenar el model.
    % coefEntrenament és el percentatge d'imatges per entrenar. 85% dona els
    % millors resultats (99%)
    waitbar(0.33, f, 'Creant sets');
    u = numel(caractUlls);
    nu = numel(caractNoUlls);

    for i = 1 : u
        totJunt(i) = caractUlls(i);
    end
    for i = u+1 : u+nu
        totJunt(i) = caractNoUlls(i-u);
    end

    barrejat = totJunt(randperm(u+nu));
    coefEntrenament = 0.85;
    limit = floor(coefEntrenament*(u+nu));    
    entrenamentUll = struct2table(barrejat(1 : limit));
    testingUll = struct2table(barrejat(limit+1 : end));
end

