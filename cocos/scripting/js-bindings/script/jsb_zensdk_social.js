var zensdk = zensdk || {};

zensdk.CODE_SUCCEED = 0;

zensdk.HttpMethod = {};
zensdk.HttpMethod.GET = 0;
zensdk.HttpMethod.POST = 1;
zensdk.HttpMethod.DELETE = 2;

zensdk.UserActionResult = {
    kLoginSucceed: 0,
    kLoginFailed: 1,
    kLogoutSucceed: 2
};

zensdk.GraphResult = {
    kGraphResultSuccess: 0,
    kGraphResultFail: 1,
    kGraphResultCancel: 2,
    kGraphResultTimeout: 3
};

zensdk.ShareResult = {
    kShareSuccess: 0,
    kShareFail: 1,
    kShareCancel: 2,
    kShareTimeOut: 3
};

zensdk.facebookInstance = jsb_zensdk.ZenSocialFacebookWrapper.getInstance;

jsb_zensdk.ZenSocialFacebookWrapper.prototype.logout = function(callback){
    this._logout();
    callback(0, {"isLoggedIn" : false});
};

jsb_zensdk.ZenSocialFacebookWrapper.prototype.api = function (path, httpmethod, params, callback) {
    if (typeof params === 'function') {
        callback = params;
        params = {};
    }
    this._api(path, httpmethod, params, function(code, msg){
        callback(code, JSON.parse(msg));
    });
};

