import "dotenv/config";
import OpenAI from "openai";

const apiKey = process.env.HHTECH_API_KEY;

if (!apiKey) {
  console.error("Chưa thiết lập HHTECH_API_KEY trong file .env");
  process.exit(1);
}

const client = new OpenAI({
  apiKey,
  baseURL: "https://hhtechapi.net/v1",
});

try {
  const response = await client.chat.completions.create({
    model: "gpt-5.5",
    messages: [
      {
        role: "user",
        content: "Xin chào",
      },
    ],
  });

  console.log(response.choices[0]?.message?.content);
} catch (error) {
  console.error("Gọi API thất bại:");

  if (error.status) {
    console.error("HTTP status:", error.status);
  }

  console.error(error.message);
}