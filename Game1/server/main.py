import asyncio
import websockets
import socket
import threading
import json

TCP_PORT = 5555
WS_PORT = 8000

clients = set()
tcp_conn = None

async def ws_handler(websocket, path):
    global tcp_conn
    clients.add(websocket)
    try:
        async for message in websocket:
            if tcp_conn:
                tcp_conn.sendall(message.encode())
    except:
        pass
    finally:
        clients.remove(websocket)

async def broadcast_state(state):
    if clients:
        await asyncio.wait([client.send(state) for client in clients])

def handle_tcp_client(conn):
    global tcp_conn
    tcp_conn = conn
    print("C++ Pac-Man connected via TCP")

    while True:
        try:
            data = conn.recv(1024)
            if not data:
                break
            asyncio.run(broadcast_state(data.decode()))
        except:
            break

    tcp_conn.close()
    tcp_conn = None
    print("C++ client disconnected")

def start_tcp_server():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("0.0.0.0", TCP_PORT))
    s.listen(1)
    print(f"TCP Server listening on port {TCP_PORT}")
    while True:
        conn, _ = s.accept()
        threading.Thread(target=handle_tcp_client, args=(conn,), daemon=True).start()

if __name__ == "__main__":
    threading.Thread(target=start_tcp_server, daemon=True).start()
    print(f"WebSocket Server running on ws://localhost:{WS_PORT}")
    asyncio.get_event_loop().run_until_complete(
        websockets.serve(ws_handler, "0.0.0.0", WS_PORT)
    )
    asyncio.get_event_loop().run_forever()
