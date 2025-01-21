#
#  ネットワークサービスの定義
#

#  ネットワークインタフェースの選択、何れか一つ選択する。

NET_IF = @(NET_IF)

#  イーサネット・ディバイスドライバの選択

NET_DEV = @(NET_DEV)

#  ネットワーク層の選択、何れか一つ選択する。

@(SUPPORT_INET4)
@(SUPPORT_INET6)

#  トランスポート層の選択

@(SUPPORT_TCP)
@(SUPPORT_UDP)

#
#  システムサービスの Makefile のインクルード
#
include $(SRCDIR)/tinet/Makefile.tinet

#
