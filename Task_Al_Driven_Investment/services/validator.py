import re
from datetime import datetime

class Validator:

    allowed_categories = [
        "Performance Update",
        "Research Insight",
        "Product Communication",
        "Marketing"
    ]

    def validate(self, record):

        if not re.match(r"^[6-9]\d{9}$", str(record.mobile)):
            return False, "Invalid Mobile"

        if not record.message.strip():
            return False, "Empty Message"

        try:
            schedule_time = datetime.strptime(record.schedule, "%Y-%m-%d %H:%M")
        except:
            return False, "Invalid datetime"

        if schedule_time < datetime.now():
            return False, "Schedule in past"

        if record.category not in self.allowed_categories:
            return False, "Invalid category"

        return True, "Valid"
    
    