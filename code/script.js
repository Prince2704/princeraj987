const API_KEY = 'd930ae79584b5e2f6faf21b1a82c7fac'; // Replace this with your API key

const cityInput = document.getElementById('city-input');
const searchBtn = document.getElementById('search-btn');
const currentDetails = document.getElementById('current-details');
const forecastDetails = document.getElementById('forecast-details');

// Fetch weather data
async function getWeatherData(city) {
  const currentWeatherURL = `https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${API_KEY}`;
  const forecastURL = `https://api.openweathermap.org/data/2.5/forecast?q=${city}&units=metric&appid=${API_KEY}`;
  
  try {
    const [currentResponse, forecastResponse] = await Promise.all([
      fetch(currentWeatherURL),
      fetch(forecastURL)
    ]);
    
    if (!currentResponse.ok || !forecastResponse.ok) {
      throw new Error('City not found');
    }
    
    const currentData = await currentResponse.json();
    const forecastData = await forecastResponse.json();
    
    displayCurrentWeather(currentData);
    displayForecast(forecastData);
  } catch (error) {
    alert(error.message);
  }
}

// Display current weather
function displayCurrentWeather(data) {
  const { name, main, weather, wind } = data;
  currentDetails.innerHTML = `
    <h3>${name}</h3>
    <img src="https://openweathermap.org/img/wn/${weather[0].icon}@2x.png" alt="${weather[0].description}" />
    <p>Temperature: ${main.temp}°C</p>
    <p>Humidity: ${main.humidity}%</p>
    <p>Wind Speed: ${wind.speed} m/s</p>
  `;
}

// Display 5-day forecast
function displayForecast(data) {
  forecastDetails.innerHTML = ''; // Clear previous forecast
  const forecastList = data.list.filter(item => item.dt_txt.includes('12:00:00'));
  
  forecastList.forEach(forecast => {
    const { dt_txt, main, weather } = forecast;
    const date = new Date(dt_txt).toLocaleDateString('en-US', { weekday: 'short', month: 'short', day: 'numeric' });
    forecastDetails.innerHTML += `
      <div class="forecast-card">
        <h3>${date}</h3>
        <img class="weather-icon" src="https://openweathermap.org/img/wn/${weather[0].icon}.png" alt="${weather[0].description}" />
        <p class="weather-data">Temp: ${main.temp}°C</p>
        <p class="weather-data">Humidity: ${main.humidity}%</p>
      </div>
    `;
  });
}

// Search button event listener
searchBtn.addEventListener('click', () => {
  const city = cityInput.value.trim();
  if (city) {
    getWeatherData(city);
  }
});
