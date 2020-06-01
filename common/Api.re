module BasicInfo = {
  let nfeKey = [%bs.raw "process.env.CNPJ_API_KEY"];
  let nfeURL = "http://legalentity.api.nfe.io/v1";

  [@decco]
  type qualification = {
    code: string,
    description: string,
  };

  [@decco]
  type partners = {
    name: string,
    qualification,
  };

  [@decco]
  type legalNature = {
    code: string,
    description: string,
  };

  [@decco]
  type economicActivities = {
    isMain: bool,
    code: string,
    description: string,
  };

  [@decco]
  type phones = {
    ddd: string,
    number: string,
    source: string,
  };

  [@decco]
  type city = {
    code: string,
    name: string,
  };

  [@decco]
  type address = {
    state: option(string),
    district: option(string),
    streetSuffix: option(string),
    street: option(string),
    number: option(string),
    postalCode: option(string),
    country: option(string),
    city: option(city),
  };

  [@decco]
  type t = {
    name: string,
    federalTaxNumber: string,
    size: string,
    openedOn: option(string),
    statusOn: option(string),
    status: option(string),
    email: option(string),
    issuedOn: option(string),
    shareCapital: float,
    unit: option(string),
    partners: array(partners),
    legalNature,
    economicActivities: array(economicActivities),
    phones: array(phones),
    address: option(address),
  };

  let get = cnpj => {
    open BsFluture;

    let path = {j|$nfeURL/legalentities/basicInfo/$cnpj?api_key=$nfeKey|j};

    tryP(() => Bs_fetch.(fetch(path) |> Js.Promise.then_(Response.json)))
    |> map(t_decode)
  };
};
