import logo from './logo.svg';
import './App.css';
import Card from './components/card';
import MQTT from 'mqtt';
import { useEffect, useState } from 'react'
 
function App() {  
  const client = MQTT.connect('mqtt://34.82.203.167:1884');
  const [temp, setTemp] = useState("")
  const [humid, setHumid] = useState("")

  useEffect(() => {
    client.subscribe('temp', (err) => {
      if (err) {
        console.error(err);
      } else {
        console.log('Subscribed to topic/temp');
      }
    });
  
    client.subscribe('humid', (err) => {
      if (err) {
        console.error(err);
      } else {
        console.log('Subscribed to topic/humid');
      }
    });
    
    client.on('message', (topic, message) => {
      switch (topic){
        case 'temp':
          setTemp(message.toString())
          break
        case 'humid':
          setHumid(message.toString())
          break
      }
      console.log(`Received message on ${topic}: ${message.toString()}`);
    });  
  }, [])

  useEffect(() => {
    return () => {
      client.unsubscribe('humi');
      client.unsubscribe('temp')
    };
  }, []);

  return (
    <div className="App">
      <header>
        <h1>Weather Dashboard</h1>
      </header>
      <Card heading="Temperature" number={temp}/>
      <Card heading="Humidity" number={humid}/>
    </div>
  );
}

export default App;
