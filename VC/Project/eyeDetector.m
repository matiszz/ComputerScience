% Carreguem les imatges
% Ulls és un struct amb la imatge, la posició dels ulls i si mira o no.
f = waitbar(0, 'Començant');
[ulls, f] = obtenirUlls(f);

% Creació del dataset de ulls / no-ulls
[caractUlls, caractNoUlls, entrenamentUll, testingUll] = crearDataset(ulls, f);

% Entrenar el model per diferenciar ulls i no ulls.
waitbar(0.4, f, 'Entrenant model ull');
modelUll = fitcsvm(entrenamentUll, 'tipus');
prediccioUll = predict(modelUll, testingUll);

% Evaluem la predicció i imprimim informació sobre la predicció
[confMatrixUll, ~] = confusionmat(prediccioUll, testingUll.tipus);
accuracyUll = (confMatrixUll(1,1) + confMatrixUll(2,2))/length(prediccioUll);
disp(['Detecció de ulls/no ulls amb exactitud de ', num2str(accuracyUll*100), '%'])

% Creació del dataset de mira / no-mira
[caractMira, caractNoMira, entrenamentMira, testingMira] = crearDatasetMirada( ulls, f );

% Entrenem el model
waitbar(0.7, f, 'Entrenant model mirada');
modelMirada = fitcsvm(entrenamentMira, 'tipus');
prediccioMirada = predict(modelMirada, testingMira);

% Evaluem la predicció
waitbar(1, f, 'Acabant');
[confMatrixMirada, ~] = confusionmat(prediccioMirada, testingMira.tipus);
accuracyMirada = (confMatrixMirada(1,1) + confMatrixMirada(2,2))/length(prediccioMirada);
disp(['Detecció de mirada amb exactitud de ', num2str(accuracyMirada*100), '%'])

close(f)