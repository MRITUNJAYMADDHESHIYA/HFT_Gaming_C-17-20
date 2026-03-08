import gspread
from oauth2client.service_account import ServiceAccountCredentials
from models.message_model import MessageRecord


class GoogleSheetService:

    def __init__(self, credentials_file, sheet_name):
        scope = ["https://spreadsheets.google.com/feeds","https://www.googleapis.com/auth/drive"]

        creds = ServiceAccountCredentials.from_json_keyfile_name(credentials_file, scope)
        client = gspread.authorize(creds)

        self.sheet = client.open(sheet_name).sheet1

############## Pending and empty row ##################
    def read_pending_rows(self):

        rows = self.sheet.get_all_records()

        records = []
        for idx, row in enumerate(rows, start=2):
            if row["Status"] == "" or row["Status"] == "Pending":

                record = MessageRecord(
                    row["Name"],
                    row["Mobile"],
                    row["Message"],
                    row["Schedule"],
                    row["Category"],
                    row["Status"],
                    row["Compliance_flag"],
                    idx
                )

                records.append(record)

        return records

    def update_status(self, row_id, status):
        self.sheet.update_cell(row_id, 6, status)

    def update_compliance(self, row_id, flag):
        self.sheet.update_cell(row_id, 7, flag)

