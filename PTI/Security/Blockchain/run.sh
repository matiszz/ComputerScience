#Run the two nodes
pkill python
python3.6 blockchain.py -p 5000 &
python3.6 blockchain.py -p 5001 &

sleep 3

#Write two transactions into node 1
curl -X POST -H "Content-Type: application/json" -d '{"sender": "A","recipient": "B", "amount": 8 }' http://localhost:5000/transactions/new
curl -X POST -H "Content-Type: application/json" -d '{"sender": "B","recipient": "C", "amount": 5 }' http://localhost:5000/transactions/new

#Mine block at node 1 
curl http://localhost:5000/mine

#See chain at node 1 
curl http://localhost:5000/chain

#Mine another block at node 1 
curl http://localhost:5000/mine

#See chain at node 1 
curl http://localhost:5000/chain

#Mine another block at node 1 
curl http://localhost:5000/mine

#See chain at node 1 
curl http://localhost:5000/chain

# At this point, node 1 should have three blocks.
# We will operate now on node 2
#Mine block at node 2 
curl http://localhost:5001/mine

#Mine another block at node 2
curl http://localhost:5001/mine

#See chain at node 2 
curl http://localhost:5000/chain

# At this point, node 2 should have two blocks.
# We will now register the nodes to each other: Node 1 will know node 2 and node 2 will know node 1.
#Register nodes in node 1
curl -X POST -H "Content-Type: application/json" -d '{"nodes":"http://localhost:5001"}' http://localhost:5000/nodes/register

#Register nodes in node 2
curl -X POST -H "Content-Type: application/json" -d '{"nodes":"http://localhost:5000"}' http://localhost:5001/nodes/register

# At this point, we want to synchronize the two chains (of node 1 and node 2). 
#The criteria is that the agreed common chain for both nodes is the one which is longer (i.e. has more blocks) and is valid (i.e. the chain of hashes is correct).
#node 1 will synchronize its chain 
curl http://localhost:5000/nodes/resolve

#node 2 will synchronize its chain 
curl http://localhost:5001/nodes/resolve