#include <store-data.hpp>

ACTION eva_store::transact(name user, string transactionId, string from, string to, string hash) {
  require_auth(user);
  
  if (user.value != name("store.data").value)
    return;

  // Init the _message table
  transactions_table _transactions(get_self(), get_self().value);
  
  // Create a message record if it does not exist
  _transactions.emplace(user, [&](auto& ts) {
    ts.key = _transactions.available_primary_key();
    ts.transactionId = transactionId;
    ts.from = from;
    ts.to = to;
    ts.hash = hash;
  });
}

ACTION eva_store::updatecoin(name user, string userId, uint64_t coin, int key= -1){
  require_auth(user);
  
  if (user.value != name("store.data").value)
    return;

  // Init the _message table
  coins_table _coins(get_self(), get_self().value);
  
  // Create a message record if it does not exist

  if(key == -1){
    _coins.emplace(user, [&](auto& ts) {
      ts.key = _coins.available_primary_key();
      ts.userId = userId;
      ts.coin = coin;
    });
  }
  else{
    auto iterator = _coins.find((uint64_t)key);
    _coins.modify(iterator, user, [&]( auto& ts ) {
      ts.userId = userId;
      ts.coin = coin;
    });
  }
}

ACTION eva_store::addreview(name user, string reviewId, string transactionId, string hash){
  require_auth(user);
  
  if (user.value != name("store.data").value)
    return;

  // Init the _message table
  reviews_table _reviews(get_self(), get_self().value);
  
  // Create a message record if it does not exist
  _reviews.emplace(user, [&](auto& ts) {
    ts.key = _reviews.available_primary_key();
    ts.reviewId = reviewId;
    ts.transactionId = transactionId;
    ts.hash = hash;
  });
}

ACTION eva_store::adddiscount(name user, string transactionId,string userId,int percent){
  require_auth(user);
  
  if (user.value != name("store.data").value)
    return;

  // Init the _message table
  discounts_table _discounts(get_self(), get_self().value);
  
  // Create a message record if it does not exist
  _discounts.emplace(user, [&](auto& ts) {
    ts.key = _discounts.available_primary_key();
    ts.transactionId = transactionId;
    ts.userId = userId;
    ts.percent = (uint64_t)percent;
  });
}

// ACTION eva_store::clear() {
//   require_auth(get_self());

//   transactions_table _transactions(get_self(), get_self().value);

//   // Delete all records in _messages table
//   auto msg_itr = _transactions.begin();
//   while (msg_itr != _transactions.end()) {
//     msg_itr = _transactions.erase(msg_itr);
//   }
// }
