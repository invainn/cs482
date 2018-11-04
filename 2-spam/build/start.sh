echo "Training..."
./training -i spam.csv -oh ham.log -os spam.log

echo "Classifying..."
./classify -i spam.csv -ih ham.log -is spam.log -o classified.log

echo "Done!"
