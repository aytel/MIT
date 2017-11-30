select City.Name, City.Population, Country.Population
from City inner join Country on City.CountryCode = Country.Code
order by cast(City.Population as float) / cast(Country.Population as float) desc, City.Name desc
limit 20;