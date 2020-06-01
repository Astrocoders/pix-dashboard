type params = {slug: string};

type props = {
  participant: Js.null(Seed.participant),
  basicInfo: Js.null(Js.Json.t),
};

module InfoBlock = {
  [@react.component]
  let make = (~title, ~children) => {
    <div className=[%tw "pt-20"]>
      <h3 className=[%tw "text-2xl"]> title->React.string </h3>
      children
    </div>;
  };
};

let default: props => React.element =
  ({participant, basicInfo}) => {
    let participant = Js.Null.toOption(participant);

    // Some malabares needed because BuckleScript represents options as undefined, which can't be serialized
    // By default by NextJs, so we gotta serialize our data again to send over the write and do all this here
    let basicInfo =
      Js.Null.toOption(basicInfo)
      ->Belt.Option.map(Api.BasicInfo.t_decode)
      ->Belt.Option.flatMap(res => res->Belt.Result.mapWithDefault(None, res => Some(res), ));

    switch (participant) {
    | None => <div> {React.string("Nada aqui")} </div>
    | Some(participant) =>
      <div>
        <h1 className=[%tw "text-6xl"]> {React.string(participant.name)} </h1>
        <h2 className=[%tw "text-3xl text-gray-400"]>
          participant.cnpj->React.string
        </h2>
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
          <InfoBlock title={j|Sócios|j}>
            {basicInfo
             ->Belt.Option.map(basicInfo => basicInfo.partners)
             ->Belt.Option.map(partners => {
                 partners->Belt.Array.map(partner => {
                   <div key={partner.name} className=[%tw "py-2"]>
                     <p className=[%tw "font-bold"]>
                       partner.name->React.string
                     </p>
                     <p className=[%tw "text-gray-600"]>
                       partner.qualification.description->React.string
                     </p>
                   </div>
                 })
               })
             ->Belt.Option.getWithDefault([||])
             ->React.array}
          </InfoBlock>
          {switch (participant.participation) {
           | "DIRETA" =>
             <InfoBlock title={j|Quem eles irão atender|j}>
               React.null
             </InfoBlock>
           | "INDIRETA"
           | _ =>
             <InfoBlock title={j|Quem está por trás|j}>
               React.null
             </InfoBlock>
           }}
          <InfoBlock title={j|Onde eles estão|j}>
            {basicInfo
             ->Belt.Option.flatMap(basicInfo => basicInfo.address)
             ->Belt.Option.map(address => {
                 <div>
                   <p>
                     {address.street
                      ->Belt.Option.getWithDefault("")
                      ->React.string}
                   </p>
                   <p>
                     {address.city
                      ->Belt.Option.mapWithDefault("", city => city.name)
                      ->React.string}
                   </p>
                 </div>
               })
             ->Belt.Option.getWithDefault(React.null)}
          </InfoBlock>
        </div>
      </div>
    };
  };

let getStaticProps: Next.GetStaticProps.t(props, params) =
  ctx => {
    open BsFluture;
    let cnpj = ctx.params.slug;

    Api.BasicInfo.get(cnpj)
    |> map(basicInfo => {
         let participant =
           Seed.getParticipantBySlug(cnpj)->Js.Null.fromOption;

         basicInfo->Belt.Result.mapWithDefault(
           {participant, basicInfo: Js.null}, basicInfo =>
           {
             participant,
             basicInfo: Js.Null.return(Api.BasicInfo.t_encode(basicInfo)),
           }
         );
       })
    |> map(props => {"props": props})
    |> promise;
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
