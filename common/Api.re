module BasicInfo = {
  let nfeKey = "";
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
    state: string,
    district: string,
    additionalInformation: string,
    streetSuffix: string,
    street: string,
    number: string,
    postalCode: string,
    country: string,
    city,
  };

  [@decco]
  type t = {
    tradeName: string,
    name: string,
    federalTaxNumber: string,
    size: string,
    openedOn: string,
    statusOn: string,
    status: string,
    email: string,
    responsableEntity: string,
    specialStatus: string,
    specialStatusOn: string,
    issuedOn: string,
    statusReason: string,
    shareCapital: int,
    registrationUnit: string,
    unit: string,
    partners: array(partners),
    legalNature,
    economicActivities: array(economicActivities),
    phones: array(phones),
    address,
  };

  let get = cnpj => {
    open BsFluture;

    let path = {j|$nfeURL/legalentities/basicInfo/$cnpj?api_key=$nfeKey|j};

    tryP(() => Bs_fetch.(fetch(path) |> Js.Promise.then_(Response.json)))
    |> map(t_decode);
  };
};
