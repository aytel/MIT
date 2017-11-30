select Country.GovernmentForm, sum(Country.SurfaceArea) as Surface from Country
group by Country.GovernmentForm
order by Surface desc limit 1;