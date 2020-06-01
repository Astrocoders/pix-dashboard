type params = {slug: string};

type props = {participant: option(Seed.participant)};

module InfoBlock = {
  [@react.component]
  let make = (~title) => {
    <div className=[%tw "pt-20"]> <h3 className=[%tw "text-2xl"]> title->React.string </h3> </div>;
  };
};

let default: props => React.element =
  ({participant}) => {
    switch (participant) {
    | None => <div> {React.string("Nada aqui")} </div>
    | Some(participant) =>
      <div>
        <h1 className=[%tw "text-6xl"]> {React.string(participant.name)} </h1>
        <h2 className=[%tw "text-3xl text-gray-400"]>{participant.cnpj->React.string}</h2>
        <h2
          className={
            [%tw "text-3xl"]
            ++ " "
            ++ (
              switch (participant.participation) {
              | "DIRETA" =>
                %tw
                "text-yellow-600"
              | "INDIRETA"
              | _ =>
                %tw
                "text-yellow-400"
              }
            )
          }>
          {React.string(participant.participation)}
        </h2>
        <div className=[%tw "divide-y pt-20"]>
          <InfoBlock title={j|Sócios|j} />
          {switch (participant.participation) {
           | "DIRETA" => <InfoBlock title={j|Quem eles irão atender|j} />
           | "INDIRETA"
           | _ => <InfoBlock title={j|Quem está por trás|j} />
           }}
          <InfoBlock title={j|Onde eles estão|j} />
        </div>
      </div>
    };
  };

let getStaticProps: Next.GetStaticProps.t(props, params) =
  ctx => {
    let props: props = {
      participant: Seed.getParticipantBySlug(ctx.params.slug),
    };

    Js.Promise.resolve({"props": props});
  };

let getStaticPaths: Next.GetStaticPaths.t(params) =
  () => {
    let paths =
      Seed.participants->Belt.Array.map(participant =>
        {
          Next.GetStaticPaths.params: {
            slug: Seed.slugify(participant),
          },
        }
      );

    Js.Promise.resolve(Next.GetStaticPaths.{paths, fallback: true});
  };
