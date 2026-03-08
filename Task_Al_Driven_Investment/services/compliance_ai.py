from groq import Groq


class ComplianceAI:

    def __init__(self, api_key):
        self.client = Groq(api_key=api_key)

    def classify(self, message):
        prompt = f"""
Classify the following investor communication message.

Categories:
Approved
Requires Review
Rejected

Message:
{message}

Only return one word.
"""

        response = self.client.chat.completions.create(
            model="llama-3.1-8b-instant",
            messages=[
                {"role": "user", "content": prompt}
            ]
        )

        result = response.choices[0].message.content.strip()
        return result
    
    