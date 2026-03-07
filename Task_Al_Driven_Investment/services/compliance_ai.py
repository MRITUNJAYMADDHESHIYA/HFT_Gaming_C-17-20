import openai

class ComplianceAI:

    def __init__(self, api_key):
        openai.api_key = api_key

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

        response = openai.ChatCompletion.create(
            model="gpt-4o-mini",
            messages=[{"role":"user","content":prompt}]
        )

        result = response['choices'][0]['message']['content'].strip()

        return result