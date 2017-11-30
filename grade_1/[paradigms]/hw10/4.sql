select Country.Name, count(City.Id) as Mills from (
    Country left join City on Country.Code = City.CountryCode and City.Population >= 1000000
)
group by Country.Name
order by Mills desc, Country.Name;