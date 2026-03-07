from services.sheet_service import GoogleSheetService
from services.validator import Validator
from services.compliance_ai import ComplianceAI
from services.scheduler import Scheduler
from services.sender import MessageSender
from workflow.workflow_manager import WorkflowManager


def main():

    print("Starting AI Workflow...")

    sheet = GoogleSheetService("C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Task_Al_Driven_Investment/credentials.json","InvestorMessages")
    print("first")
    
    validator = Validator()
    compliance = ComplianceAI("OPENAI_API_KEY")
    scheduler = Scheduler()
    sender = MessageSender()

    manager = WorkflowManager(sheet,validator,compliance,scheduler,sender)

    print("Processing rows from Google Sheet...")
    manager.process()

    print("Scheduler started... waiting for scheduled messages.")
    scheduler.run()


if __name__ == "__main__":
    main()

    