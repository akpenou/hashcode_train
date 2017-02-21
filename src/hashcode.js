const fs = require('fs')
const _ = require('lodash')

const parsing = file => {
  const raw = fs.readFileSync(file, 'utf8').split('\n').slice(0, -1)
  const [rows, cols, minIng, maxArea] = raw[0].split(' ').map(n => parseInt(n, 10))
  const data = raw.slice(1).map(row => row.split(''))

  return {
    meta: { rows, cols, minIng, maxArea },
    data,
  }
}

const getForms = (min, max) => {
  const range = _.range(1, max + 1)

  return _.filter(_.flatMap(range, y =>
    _.map(range, x => {
      if (min <= (x * y) && (x * y) <= max)
        return [x, y]
    })
  ), undefined)
}

const isValid = ({ posX, posY }, { formX, formY }, minIng, data, { tabX, tabY }) => {
  if (posX + formX > tabX || posY + formY > tabY)
    return 0

  const [m, t] = [0, 0]

  for (const x of _.range(formX)) {
    for (const y of _.range(formY)) {
      const item = data[posY + y][posX + x]

      if (!['M', 'T'].includes(item))
        throw new Error('Value error')

      m += _.isEqual(item, 'M') ? 1 : 0
      t += _.isEqual(item, 'T') ? 1 : 0

      if (m >= minIng && t >= minIng)
        return 1
    }
  }
}

const makeCoords = (maxX, maxY) => {
  const coords = []

  for (const y of _.range(maxY)) {
    for (const x of _.range(maxX)) {
      coords.push([x, y])
    }
  }

  return coords
}

(() => {
  try {
    const script = __filename.split('/').slice(-1)[0]
    const file = process.argv[2]

    if (!file) throw new Error(`Usage: node ${script} file`)

    const { meta, data } = parsing(file)

    const forms = getForms(2 * meta.minIng, meta.maxArea)

  } catch (err) {
    console.error(err)
    process.exit(1)
  }
})()
