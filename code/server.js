const express = require('express');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

app.post('/chat', (req, res) => {
  const { message } = req.body;

  // Simple chatbot logic
  let response = "Sorry, I didn't understand that.";
  if (message.includes('hello')) response = "Hi there! How can I help you?";
  if (message.includes('bye')) response = "Goodbye! Have a great day!";

  res.json({ response });
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
