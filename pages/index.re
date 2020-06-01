%raw
"require('../styles/main.css')";

open Util.ReactStuff;

module P = {
  [@react.component]
  let make = (~children) => <p className="mb-2"> children </p>;
};

[@react.component]
let make = () => {
  let (searchText, setSearch) = React.useState(_ => "");

  let search: array(Seed.participant) => array(Seed.participant) =
    participants => {
      // TODO add fuzzy search
      participants->Belt.Array.keep(_participant => true);
    };

  <div>
    <h1 className="text-3xl font-semibold">
      "Empresas no PIX"->ReasonReact.string
    </h1>
    <P>
      {j| Veja quais empresas estão na lista de espera para participarem do PIX|j}
      ->s
    </P>
    <div className=[%tw "py-5"]>
      <input
        placeholder="Busca..."
        value=searchText
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;
          setSearch(value);
        }}
      />
    </div>
    {Seed.participants
     ->search
     ->Belt.Array.map(participant => {
         <P key={participant.cnpj}>
           {<a href={"/participant/" ++ Seed.slugify(participant)}>
              participant.name->React.string
            </a>}
         </P>
       })
     ->React.array}
  </div>;
};

let default = make;
