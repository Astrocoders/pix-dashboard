const Papa = require("papaparse");
const path = require("path");
const fs = require("fs");

const filePath = path.join(__dirname, "../data", "participantes.csv");
const seedPath = path.join(__dirname, "../data", "seed.json");

const clean = (data) => {
  return (
    data
      // Remove invalid CNPJ
      .filter(({ cnpj }) => Boolean(cnpj))
      .filter(({ participation }) => Boolean(participation))

      .map(({ cnpj, name, participation, index }) => ({
        cnpj: cnpj.trim(),
        name: name.trim(),
        participation: participation.trim(),
        index: index.trim(),
      }))
  );
};

const fromCSV = () => {
  const { data } = Papa.parse(fs.readFileSync(filePath).toString(), {
    header: true,
  });

  console.log(data);

  return data;
};

const writeSeed = (data) => {
  fs.writeFileSync(seedPath, JSON.stringify(data));
};

const main = () => {
  writeSeed(clean(fromCSV()));
};

main();
