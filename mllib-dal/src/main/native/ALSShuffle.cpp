#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <oneapi/ccl.hpp>

#include "ALSShuffle.h"

using namespace std;

std::vector<Rating> recvData;

jlong getPartiton(jlong key, jlong totalKeys, long nBlocks) {

  jlong itemsInBlock = totalKeys / nBlocks;

  return min(key / itemsInBlock, nBlocks - 1);
}

// Compares two Rating according to userId. 
bool compareRatingByUser(Rating r1, Rating r2)
{ 
  if (r1.user < r2.user)
    return true;
  if (r1.user == r2.user && r1.item < r2.item)  
    return true;
  return false;
}

bool compareRatingUserEquality(Rating &r1, Rating &r2) {
    return r1.user == r2.user;
}

int distinct_count(std::vector<Rating> &data) {
  long curUser = -1;
  long count = 0;
  for (auto i : data) {
    if (i.user > curUser) {
      curUser = i.user;
      count += 1;
    }    
  }
  return count;
}

Rating * shuffle_all2all(ccl::communicator &comm, std::vector<RatingPartition> &partitions, size_t nBlocks, size_t &newRatingsNum, size_t &newCsrRowNum) {
  size_t sendBufSize = 0;
  size_t recvBufSize = 0;
  vector<size_t> perNodeSendLens(nBlocks);
  vector<size_t> perNodeRecvLens(nBlocks);

  ByteBuffer sendData;  

  // Calculate send buffer size
  for (size_t i = 0; i < nBlocks; i++) {      
      perNodeSendLens[i] = partitions[i].size() * RATING_SIZE;
      // cout << "rank " << rankId << " Send partition " << i << " size " << perNodeSendLens[i] << endl;
      sendBufSize += perNodeSendLens[i];
  }
  cout << "sendData size " << sendBufSize << endl;
  sendData.resize(sendBufSize);

  // Fill in send buffer
  size_t offset = 0;
  for (size_t i = 0; i < nBlocks; i++)
  {
    memcpy(sendData.data()+offset, partitions[i].data(), perNodeSendLens[i]);
    offset += perNodeSendLens[i];
  }

  // Send lens first  
  ccl::alltoall(perNodeSendLens.data(), perNodeRecvLens.data(), sizeof(size_t), ccl::datatype::uint8, comm).wait();

  // Calculate recv buffer size
  for (size_t i = 0; i < nBlocks; i++) {
      // cout << "rank " << rankId << " Recv partition " << i << " size " << perNodeRecvLens[i] << endl;
      recvBufSize += perNodeRecvLens[i];
  }  

  int ratingsNum = recvBufSize / RATING_SIZE;
  recvData.resize(ratingsNum);

  // Send data
  ccl::alltoallv(sendData.data(), perNodeSendLens, recvData.data(), perNodeRecvLens, ccl::datatype::uint8, comm).wait();  

  sort(recvData.begin(), recvData.end(), compareRatingByUser);

  // for (auto r : recvData) {
  //   cout << r.user << " " << r.item << " " << r.rating << endl;
  // }

  newRatingsNum = recvData.size();
  // RatingPartition::iterator iter = std::unique(recvData.begin(), recvData.end(), compareRatingUserEquality);
  // newCsrRowNum = std::distance(recvData.begin(), iter);
  newCsrRowNum = distinct_count(recvData);

  cout << "newRatingsNum: " << newRatingsNum << " newCsrRowNum: " << newCsrRowNum << endl;

  return recvData.data();
}
