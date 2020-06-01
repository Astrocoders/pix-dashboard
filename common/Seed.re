type participant = {
  name: string,
  cnpj: string,
  participation: string,
}
let participants: array(participant) = [%raw {|require('../data/seed.json')|}]

let slugify: participant => string = ({cnpj}) => cnpj|>Js.String.replaceByRe([%re {|/\D+/g|}], "")

let getParticipantBySlug = slug =>
  participants->Belt.Array.getBy((participant) => slugify(participant) == slug)