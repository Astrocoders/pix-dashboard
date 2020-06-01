const Papa = require('papaparse')
const path = require('path')
const fs = require('fs')

const filePath = path.join(__dirname, '../data', 'participantes.csv') 
const seedPath = path.join(__dirname, '../data', 'seed.json') 

const clean = (data) => {
  return data.filter(({cnpj}) => Boolean(cnpj))
}

const fromCSV = () => {
  const {data} = Papa.parse(
    fs.readFileSync(filePath).toString(),
    {
      header: true
    }
  )

  console.log(data)

  return data
}

const writeSeed = (data) => {
  fs.writeFileSync(seedPath, JSON.stringify(data))
}

const main = () => {
  writeSeed(clean(fromCSV()))
}

main()