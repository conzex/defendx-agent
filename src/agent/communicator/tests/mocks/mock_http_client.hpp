#include <gmock/gmock.h>

#include <ihttp_client.hpp>

using intStringTuple = std::tuple<int, std::string>;

class MockHttpClient : public http_client::IHttpClient
{
public:
    MOCK_METHOD(boost::beast::http::request<boost::beast::http::string_body>,
                CreateHttpRequest,
                (const http_client::HttpRequestParams& params),
                (override));

    MOCK_METHOD(boost::asio::awaitable<void>,
                Co_PerformHttpRequest,
                (std::shared_ptr<std::string> token,
                 http_client::HttpRequestParams params,
                 std::function<boost::asio::awaitable<intStringTuple>(const int)> messageGetter,
                 std::function<void()> onUnauthorized,
                 std::time_t connectionRetry,
                 std::time_t batchInterval,
                 int batchSize,
                 std::function<void(const int, const std::string&)> onSuccess,
                 std::function<bool()> loopRequestCondition),
                (override));

    MOCK_METHOD(boost::beast::http::response<boost::beast::http::dynamic_body>,
                PerformHttpRequest,
                (const http_client::HttpRequestParams& params),
                (override));

    MOCK_METHOD(
        std::optional<std::string>,
        AuthenticateWithUuidAndKey,
        (const std::string& host, const std::string& userAgent, const std::string& uuid, const std::string& key),
        (override));

    MOCK_METHOD(
        std::optional<std::string>,
        AuthenticateWithUserPassword,
        (const std::string& host, const std::string& userAgent, const std::string& user, const std::string& password),
        (override));

    MOCK_METHOD(boost::beast::http::response<boost::beast::http::dynamic_body>,
                PerformHttpRequestDownload,
                (const http_client::HttpRequestParams& params, const std::string& dstFilePath),
                (override));
};
