//
// Created by mwo on 7/01/17.
//

#define MYSQLPP_SSQLS_NO_STATICS 1

#include "MySqlAccounts.h"
#include "TxSearch.h"

#include "ssqlses.h"

namespace xmreg
{

MysqlTransactionWithOutsAndIns::MysqlTransactionWithOutsAndIns(shared_ptr<MySqlConnector> _conn)
        : conn{_conn}
{}

bool
MysqlTransactionWithOutsAndIns::select(
        const uint64_t &address_id,
        vector<XmrTransactionWithOutsAndIns>& txs)
{

    Query query = conn->query(XmrTransactionWithOutsAndIns::SELECT_STMT);
    query.parse();

    try
    {
        query.storein(txs, address_id);

        if (!txs.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception &e) {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception &e) {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

bool
MysqlTransactionWithOutsAndIns::select_for_tx(
        const uint64_t &tx_id,
        vector<XmrTransactionWithOutsAndIns>& txs)
{

    Query query = conn->query(XmrTransactionWithOutsAndIns::SELECT_STMT2);
    query.parse();

    try
    {
        query.storein(txs, tx_id);

        if (!txs.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception &e) {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception &e) {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


MysqlInputs::MysqlInputs(shared_ptr<MySqlConnector> _conn): conn {_conn}
{}

bool
MysqlInputs::select(const uint64_t& address_id, vector<XmrInput>& ins)
{

    Query query = conn->query(XmrInput::SELECT_STMT);
    query.parse();

    try
    {
        query.storein(ins, address_id);

        if (!ins.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

bool
MysqlInputs::select_for_tx(const uint64_t& address_id, vector<XmrInput>& ins)
{

    Query query = conn->query(XmrInput::SELECT_STMT2);
    query.parse();

    try
    {
        query.storein(ins, address_id);

        if (!ins.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


bool
MysqlInputs::select_for_out(const uint64_t& output_id, vector<XmrInput>& ins)
{

    Query query = conn->query(XmrInput::SELECT_STMT3);
    query.parse();

    try
    {
        query.storein(ins, output_id);

        if (!ins.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


uint64_t
MysqlInputs::insert(const XmrInput& in_data)
{

//        static shared_ptr<Query> query;
//
//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrInput::INSERT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }


    Query query = conn->query(XmrInput::INSERT_STMT);
    query.parse();

    // cout << query << endl;

    try
    {
        SimpleResult sr = query.execute(in_data.account_id,
                                        in_data.tx_id,
                                        in_data.output_id,
                                        in_data.key_image,
                                        in_data.amount,
                                        in_data.timestamp);

        if (sr.rows() == 1)
            return sr.insert_id();

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }

    return 0;
}



MysqlOutpus::MysqlOutpus(shared_ptr<MySqlConnector> _conn): conn {_conn}
{}

bool
MysqlOutpus::select(const uint64_t& address_id, vector<XmrOutput>& outs)
{
    Query query = conn->query(XmrOutput::SELECT_STMT);
    query.parse();

    try
    {
        query.storein(outs, address_id);

        if (!outs.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

bool
MysqlOutpus::select_for_tx(const uint64_t& tx_id, vector<XmrOutput>& outs)
{
    Query query = conn->query(XmrOutput::SELECT_STMT2);
    query.parse();

    try
    {
        query.storein(outs, tx_id);

        if (!outs.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


bool
MysqlOutpus::exist(const string& output_public_key_str, XmrOutput& out)
{

    Query query = conn->query(XmrOutput::EXIST_STMT);
    query.parse();

    try
    {

        vector<XmrOutput> outs;

        query.storein(outs, output_public_key_str);

        if (outs.empty())
        {
            return false;
        }

        out = outs.at(0);

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return true;
}



uint64_t
MysqlOutpus::insert(const XmrOutput& out_data)
{

//        static shared_ptr<Query> query;
//
//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrOutput::INSERT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }


    Query query = conn->query(XmrOutput::INSERT_STMT);
    query.parse();

    // cout << query << endl;

    try
    {
        SimpleResult sr = query.execute(out_data.account_id,
                                        out_data.tx_id,
                                        out_data.out_pub_key,
                                        out_data.tx_pub_key,
                                        out_data.amount,
                                        out_data.global_index,
                                        out_data.out_index,
                                        out_data.mixin,
                                        out_data.timestamp);

        if (sr.rows() == 1)
            return sr.insert_id();

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }

    return 0;
}



MysqlTransactions::MysqlTransactions(shared_ptr<MySqlConnector> _conn): conn {_conn}
{}

bool
MysqlTransactions::select(const uint64_t& address_id, vector<XmrTransaction>& txs)
{
//
//        static shared_ptr<Query> query;
//
//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(
//                    XmrTransaction::SELECT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }

    Query query = conn->query(XmrTransaction::SELECT_STMT);
    query.parse();

    try
    {
        query.storein(txs, address_id);

        if (!txs.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


uint64_t
MysqlTransactions::insert(const XmrTransaction& tx_data)
{

//        static shared_ptr<Query> query;
//
//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrTransaction::INSERT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }


    Query query = conn->query(XmrTransaction::INSERT_STMT);
    query.parse();

    // cout << query << endl;

    try
    {
        SimpleResult sr = query.execute(tx_data.hash,
                                        tx_data.prefix_hash,
                                        tx_data.account_id,
                                        tx_data.total_received,
                                        tx_data.total_sent,
                                        tx_data.unlock_time,
                                        tx_data.height,
                                        tx_data.coinbase,
                                        tx_data.payment_id,
                                        tx_data.mixin,
                                        tx_data.timestamp);

        if (sr.rows() == 1)
            return sr.insert_id();

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }

    return 0;
}


bool
MysqlTransactions::exist(const uint64_t& account_id, const string& tx_hash_str, XmrTransaction& tx)
{

    Query query = conn->query(XmrTransaction::EXIST_STMT);
    query.parse();

    try
    {

        vector<XmrTransaction> outs;

        query.storein(outs, account_id, tx_hash_str);

        if (outs.empty())
        {
            return false;
        }

        tx = outs.at(0);

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return true;
}


uint64_t
MysqlTransactions::get_total_recieved(const uint64_t& account_id)
{
    Query query = conn->query(XmrTransaction::SUM_XMR_RECIEVED);
    query.parse();

    try
    {
        StoreQueryResult sqr = query.store(account_id);

        if (!sqr)
        {
            return 0;
        }

        Row row = sqr.at(0);

        return row["total_received"];
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }
}

MysqlPayments::MysqlPayments(shared_ptr<MySqlConnector> _conn): conn {_conn}
{}

bool
MysqlPayments::select(const string& address, vector<XmrPayment>& payments)
{

    Query query = conn->query(XmrPayment::SELECT_STMT);
    query.parse();

    try
    {
        query.storein(payments, address);

        if (!payments.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

bool
MysqlPayments::select_by_payment_id(const string& payment_id, vector<XmrPayment>& payments)
{

    Query query = conn->query(XmrPayment::SELECT_STMT2);
    query.parse();

    try
    {
        query.storein(payments, payment_id);

        if (!payments.empty())
        {
            return true;
        }
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}


uint64_t
MysqlPayments::insert(const XmrPayment& payment_data)
{

    Query query = conn->query(XmrPayment::INSERT_STMT);
    query.parse();

    // cout << query << endl;

    try
    {
        SimpleResult sr = query.execute(payment_data.address,
                                        payment_data.payment_id,
                                        payment_data.tx_hash,
                                        payment_data.request_fulfilled,
                                        payment_data.payment_address,
                                        payment_data.import_fee);

        if (sr.rows() == 1)
            return sr.insert_id();

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }

    return 0;
}


bool
MysqlPayments::update(XmrPayment& payment_orginal, XmrPayment& payment_new)
{

    Query query = conn->query();

    try
    {
        query.update(payment_orginal, payment_new);

        SimpleResult sr = query.execute();

        if (sr.rows() == 1)
            return true;
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return false;
    }

    return false;
}


map<string, shared_ptr<TxSearch>> MySqlAccounts::searching_threads;

MySqlAccounts::MySqlAccounts()
{
    // create connection to the mysql
    conn            = make_shared<MySqlConnector>();

    // use same connection when working with other tables
    mysql_tx        = make_shared<MysqlTransactions>(conn);
    mysql_out       = make_shared<MysqlOutpus>(conn);
    mysql_in        = make_shared<MysqlInputs>(conn);
    mysql_payment   = make_shared<MysqlPayments>(conn);
    mysql_tx_inout  = make_shared<MysqlTransactionWithOutsAndIns>(conn);

}


bool
MySqlAccounts::select(const string& address, XmrAccount& account)
{

//        static shared_ptr<Query> query;
//
//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrAccount::SELECT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }

    Query query = conn->query(XmrAccount::SELECT_STMT);
    query.parse();

    try
    {
        vector<XmrAccount> res;
        query.storein(res, address);

        if (!res.empty())
        {
            account = res.at(0);
            return true;
        }

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }
    catch (std::exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

bool
MySqlAccounts::select(const int64_t& acc_id, XmrAccount& account)
{

    //static shared_ptr<Query> query;

//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrAccount::SELECT_STMT2);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }

    Query query = conn->query(XmrAccount::SELECT_STMT2);
    query.parse();

    try
    {
        vector<XmrAccount> res;
        query.storein(res, acc_id);

        if (!res.empty())
        {
            account = res.at(0);
            return true;
        }

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
    }

    return false;
}

uint64_t
MySqlAccounts::insert(const string& address, const uint64_t& current_blkchain_height)
{

    //    static shared_ptr<Query> query;

//        if (!query)
//        {
//            Query q = MySqlConnector::getInstance().query(XmrAccount::INSERT_STMT);
//            q.parse();
//            query = shared_ptr<Query>(new Query(q));
//        }


    Query query = conn->query(XmrAccount::INSERT_STMT);
    query.parse();

    // cout << query << endl;

    try
    {
        // scanned_block_height and start_height are
        // set to current blockchain height
        // when account is created.

        SimpleResult sr = query.execute(address,
                                        current_blkchain_height,
                                        current_blkchain_height);

        if (sr.rows() == 1)
            return sr.insert_id();

    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return 0;
    }

    return 0;
}

uint64_t
MySqlAccounts::insert_tx(const XmrTransaction& tx_data)
{
    return mysql_tx->insert(tx_data);
}

uint64_t
MySqlAccounts::insert_output(const XmrOutput& tx_out)
{
    return mysql_out->insert(tx_out);
}

uint64_t
MySqlAccounts::insert_input(const XmrInput& tx_in)
{
    return mysql_in->insert(tx_in);
}

bool
MySqlAccounts::select_txs(const string& xmr_address, vector<XmrTransaction>& txs)
{
    // having address first get its address_id


    // a placeholder for exciting or new account data
    xmreg::XmrAccount acc;

    // select this account if its existing one
    if (!select(xmr_address, acc))
    {
        cerr << "Address" << xmr_address << "does not exist in database" << endl;
        return false;
    }

    return mysql_tx->select(acc.id, txs);
}

bool
MySqlAccounts::select_txs(const uint64_t& account_id, vector<XmrTransaction>& txs)
{
    return mysql_tx->select(account_id, txs);
}


bool
MySqlAccounts::select_txs_with_inputs_and_outputs(const uint64_t& account_id,
                                   vector<XmrTransactionWithOutsAndIns>& txs)
{
    return mysql_tx_inout->select(account_id, txs);
}


bool
MySqlAccounts::select_outputs(const uint64_t& account_id, vector<XmrOutput>& outs)
{
    return mysql_out->select(account_id, outs);
}

bool
MySqlAccounts::select_outputs_for_tx(const uint64_t& tx_id, vector<XmrOutput>& outs)
{
    return mysql_out->select_for_tx(tx_id, outs);
}

bool
MySqlAccounts::select_inputs(const uint64_t& account_id, vector<XmrInput>& ins)
{
    return mysql_in->select(account_id, ins);
}

bool
MySqlAccounts::select_inputs_for_tx(const uint64_t& tx_id, vector<XmrTransactionWithOutsAndIns>& ins)
{
    return mysql_tx_inout->select_for_tx(tx_id, ins);
}

bool
MySqlAccounts::select_inputs_for_out(const uint64_t& output_id, vector<XmrInput>& ins)
{
    return mysql_in->select_for_out(output_id, ins);
}

bool
MySqlAccounts::output_exists(const string& output_public_key_str, XmrOutput& out)
{
    return mysql_out->exist(output_public_key_str, out);
}

bool
MySqlAccounts::tx_exists(const uint64_t& account_id, const string& tx_hash_str, XmrTransaction& tx)
{
    return mysql_tx->exist(account_id, tx_hash_str, tx);
}

uint64_t
MySqlAccounts::insert_payment(const XmrPayment& payment)
{
    return mysql_payment->insert(payment);
}

bool
MySqlAccounts::select_payment_by_id(const string& payment_id, vector<XmrPayment>& payments)
{
    return mysql_payment->select_by_payment_id(payment_id, payments);
}

bool
MySqlAccounts::select_payment_by_address(const string& address, vector<XmrPayment>& payments)
{
    return mysql_payment->select(address, payments);
}

bool
MySqlAccounts::select_payment_by_address(const string& address, XmrPayment& payment)
{

    vector<XmrPayment> payments;

    bool r = mysql_payment->select(address, payments);

    if (!r)
    {
        return false;
    }

    if (payments.empty())
    {
        return false;
    }

    // always get last payment details.
    payment = payments.back();

    return r;
}

bool
MySqlAccounts::update_payment(XmrPayment& payment_orginal, XmrPayment& payment_new)
{
    return mysql_payment->update(payment_orginal, payment_new);
}

uint64_t
MySqlAccounts::get_total_recieved(const uint64_t& account_id)
{
    return mysql_tx->get_total_recieved(account_id);
}


bool
MySqlAccounts::update(XmrAccount& acc_orginal, XmrAccount& acc_new)
{

    Query query = conn->query();

    try
    {
        query.update(acc_orginal, acc_new);

        SimpleResult sr = query.execute();

        if (sr.rows() == 1)
            return true;
    }
    catch (mysqlpp::Exception& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return false;
    }

    return false;
}



bool
MySqlAccounts::start_tx_search_thread(XmrAccount acc)
{
    std::lock_guard<std::mutex> lck (searching_threads_map_mtx);

    if (searching_threads.count(acc.address) > 0)
    {
        // thread for this address exist, dont make new one
        cout << "Thread exisist, dont make new one" << endl;
        return false;
    }

    // make a tx_search object for the given xmr account
    searching_threads[acc.address] = make_shared<TxSearch>(acc);

    // start the thread for the created object
    std::thread t1 {&TxSearch::search, searching_threads[acc.address].get()};
    t1.detach();

    return true;
}

bool
MySqlAccounts::ping_search_thread(const string& address)
{
    std::lock_guard<std::mutex> lck (searching_threads_map_mtx);

    if (searching_threads.count(address) == 0)
    {
        // thread does not exist
        cout << "does not exist" << endl;
        return false;
    }

    searching_threads[address].get()->ping();

    return true;
}

bool
MySqlAccounts::set_new_searched_blk_no(const string& address, uint64_t new_value)
{
    std::lock_guard<std::mutex> lck (searching_threads_map_mtx);

    if (searching_threads.count(address) == 0)
    {
        // thread does not exist
        cout << " thread does not exist" << endl;
        return false;
    }

    searching_threads[address].get()->set_searched_blk_no(new_value);

    return true;
}


void
MySqlAccounts::clean_search_thread_map()
{
    std::lock_guard<std::mutex> lck (searching_threads_map_mtx);

    for (auto st: searching_threads)
    {
        if (st.second->still_searching() == false)
        {
            cout << st.first << " still searching: " << st.second->still_searching() << endl;
            searching_threads.erase(st.first);
        }
    }
}





}