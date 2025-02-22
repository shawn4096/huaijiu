// shutdown.c with time loop.
// by snowman@SJ  22/02/1999

#include <ansi.h>
#include <mudlib.h>
#include <net/daemons.h>

int counting = 0;
int min = 3;

int help (object me)
{
        write(@HELP
指令格式: reboot < min|now >
 
例：
    reboot       :  显示目前的信息，如果没在reboot当中，显示本信息。
    reboot now   :  马上重新起动游戏。
    reboot 3     :  等三分钟，然后重新起动游戏。
    reboot cancel:  取消重起动。
    
HELP
);
        return 1;
}

private int start_shutdown()
{
        if( !intp(min) ) min = 3; 
        message("system",HIW"\n\t\t"+CHINESE_MUD_NAME+HIW"将在 "HIR+chinese_number(min)+HIW" 分钟后重新启动，请在线玩家做好准备。\n\n" NOR, users() );
        call_out("countdown", 60);
        counting = 1;
        return 1;
}


int main(object me, string arg)
{
        string wiz_status;
        int time;

        if( me != this_player(1) ) return 0;

        wiz_status = SECURITY_D->get_status(me);
        if( wiz_status != "(admin)" && wiz_status != "(arch)" && wiz_status != "(assist)")
                return notify_fail("只有 (arch) 以上的巫师才能重新启动"+CHINESE_MUD_NAME+"。\n");

        seteuid(getuid());
 
        if (!arg || arg == "?"){
        	if(counting == 0) 
        		return help(me);
        	return notify_fail(CHINESE_MUD_NAME+HIW"正在倒计时中，离重新启动还有"HIR+ chinese_number(min) + HIW"分钟。\n"NOR);
        }

	if( arg == "cancel" ){
		remove_call_out("countdown");
		remove_call_out("do_shutdown");
		counting = 0;
		min = 3;
		message("system","\n\n\t\t"+CHINESE_MUD_NAME+HIW"重新启动"HIR" 取消 "HIW"，请各位谅解。\n\n"NOR,users() );
		return notify_fail(CHINESE_MUD_NAME+HIW"重新启动取消。\n"NOR);
	}
	 
 	log_file("static/CRASHES", geteuid(me) + " reboot "+CHINESE_MUD_NAME+" on: "
                + ctime(time()) + "\n");
        write_file("/log/static/LASTCRASH", geteuid(me) + " reboot "+CHINESE_MUD_NAME+" on: "
                + ctime(time()) + "\n", 1);
                
        if (arg == "now") {
                message("system","\n\n\t\t"+CHINESE_MUD_NAME+HIW"重新启动。请在线玩家退出，请稍候一分钟再尝试连线。\n\n"NOR,users() );
                call_out("do_shutdown", 1);
                return 1;
        }
 
        if (sscanf(arg,"%d", time) != 1
        || !intp(time) 
        || time < 1) 
        	return help(me);
        
        if(counting != 0) 
        	return notify_fail(HIW"MUD已经在 shutdown 了。\n"NOR);
        
        min = time;
        if(start_shutdown())
           	write("Starting shutdown... \n");

        else return notify_fail ("定时Reboot有问题，请检查 /cmds/arch/reboot.c  \n");
        return 1;
}

private void countdown()
{
        min--;
        if( min ) {
                message("system",HIW"\n\t\t"+CHINESE_MUD_NAME+HIW"将在 "HIR+ chinese_number(min) + HIW" 分钟后重新启动，请在线玩家做好准备。\n\n"NOR, users() );
                call_out("countdown", 60, min);
        } else {
                message("system",HIW"\n\n\t\t"+CHINESE_MUD_NAME+HIW"重新启动。请在线玩家退出，稍候再尝试连线。\n\n"NOR,users() );
                call_out("do_shutdown", 1);
        }
}

private void do_shutdown()
{
        int i;
        object *user, link_ob;

        if( find_object(DNS_MASTER) ) DNS_MASTER->send_shutdown();

        user = filter_array(objects(), (: userp :));
        for(i=0; i<sizeof(user); i++) {
                if( !environment(user[i]) ) continue;
                user[i]->save();
                link_ob = user[i]->query_temp("link_ob");
                if( objectp(link_ob) ) link_ob->save();
        }

        shutdown(0);
}
