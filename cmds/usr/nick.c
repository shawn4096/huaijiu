// nick.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !arg )
		return notify_fail(me->query("nickname")?"你目前的绰号是：「"+me->query("nickname")+"」\n":"你目前没有任何绰号。\n");
	
	if (arg == "none") {
      		me->delete("nickname");
      		write("您的绰号被删除了。\n");
      		return 1;
    	}
    	
    	arg = explode(arg+"\n", "\n")[0];
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);
	if (!strlen(strip(arg))) return notify_fail("你到底输入的是什么内容啊？\n");
	if (strlen(strip(arg)) > 24) return notify_fail("你的绰号太长了，想一个短一点的、响亮一点的。\n");

	me->set("nickname", arg + NOR);
	
	write("恭喜！您现在的新绰号是：「"+me->query("nickname")+"」\n");
	return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : nick <外号>|none
 
这个指令可以让你为自己取一个响亮的名号或头衔，nick none 为删除。
你如果希望在绰号中使用 ANSI 的控制字元改变颜色，可以用以下的控制字串：

HELP
"                        $NOR$ - 恢复正常颜色\n"
"$RED$ - "RED"红色"NOR"		$HIR$ - "HIR"亮红色\n"NOR
"$GRN$ - "GRN"绿色"NOR"		$HIG$ - "HIG"亮绿色\n"NOR
"$YEL$ - "YEL"土黄色"NOR"		$HIY$ - "HIY"黄色\n"NOR
"$BLU$ - "BLU"深蓝色"NOR"		$HIB$ - "HIB"蓝色\n"NOR
"$MAG$ - "MAG"浅紫色"NOR"		$HIM$ - "HIM"粉红色\n"NOR
"$CYN$ - "CYN"蓝绿色"NOR"		$HIC$ - "HIC"天青色\n"NOR
"$WHT$ - 浅灰色		$HIW$ - "HIW"白色\n"NOR
@HELP 

其中系统自动会在字串尾端加一个 $NOR$。
HELP
);
        return 1;
}
