select Country.Name, Country.Population, Country.SurfaceArea from
(City inner join Country on Country.Code = City.CountryCode)
left join Capital on Capital.CountryCode = Country.Code
group by Country.Name
having max(City.Population) = City.Population and not City.Id = Capital.CityId
order by cast(Country.Population as float) / cast(Country.SurfaceArea as float) desc,
Country.Name;