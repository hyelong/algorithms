import SimpleHTTPServer
import SocketServer

PORT = 8000

Handler = SimpleHTTPServer.SimpleHTTPRequestHandler
Handler.extensions_map.update({
            '': 'application/octet-stream', # Default
            '.py': 'text/plain',
            '.cpp': 'text/plain',
            '.java': 'text/plain',
            '.js': 'text/plain',
                                            })
Handler.extensions_map.update(dict([(k, v + ';charset=UTF-8') for k, v in  Handler.extensions_map.items()]))
httpd = SocketServer.TCPServer(("", PORT), Handler)

print "serving at port", PORT
httpd.serve_forever()
