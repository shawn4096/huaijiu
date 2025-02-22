// $Filename:/cmds/usr/cgift.c$ generated comment change it if the path was changed
// YUJ@SJ 2001-11-02
// Modified by LOOKLOVE@SJ 引入乘幂计算，大大优化。
// 2002/4/29
// 改为玩家自行修改属性

// Exp在 100K 以上可以修改属性。
#define MIN_EXP 100000
// 剩余EXP比率等于100%减去每点扣除比率
// 当前修改每点属性，扣除exp比率为5%
#define RATE 0.9500

inherit F_CLEAN_UP;
#include <ansi.h>

int help();

static mapping gift_desc = ([
	"str":"膂力",
	"con":"根骨",
	"dex":"身法",
	"int":"悟性"
]);

static string *gift = keys(gift_desc);

// 统一过滤 by Lklv
string check(object me)
{
	string msg;

	if ((int)me->query("combat_exp") < MIN_EXP)
		msg = HIY"系统提示："NOR"抱歉，你的经验不够 "+MIN_EXP+" ，无法修改属性。\n";
	if (me->is_ghost())
		msg = HIY"系统提示："NOR"抱歉，你的状态不稳定，现在无法修改属性。\n";
	return msg;
}

// yuj 新公式，利用循环算法。
int check_exp(int exp, int num)
{
        while (num--) exp -= exp / 100;
        return exp;
}

int main(object me, string arg)
{
	string msg, from, to;
	int exp, num, newexp, tmpexp;

	if (!me) return 0;
        if (!me->query_temp("cgift")) return notify_fail("请先使用回天再造丹来获取调整先天属性的机会。\n");
	if (!arg) return help();

	if ( stringp(msg = check(me)) )
		return notify_fail(msg);

	exp = me->query("combat_exp");

	if (sscanf(arg, "%d %s to %s", num, from, to) == 3){		
		if (member_array(from, gift) < 0)
			return notify_fail("你要扣除什么天赋？\n");
		if (member_array(to, gift) < 0)
			return notify_fail("你要增加什么天赋？\n");
		if (from == to || num<0 )
			return notify_fail("检查一下，输入错误，可能眼花。\n");
		if(exp<1000000 && from=="int")
			return notify_fail("你的经验值小于1M，不能将悟性减少。\n");
		if (me->query(from) <= 10)
			return notify_fail("你的"+gift_desc[from]+"不能再减少了。\n");
		if ( ((int)me->query(from) - num) < 10)
			return notify_fail("你的"+gift_desc[from]+"减少"+num+"点后将少于10点，不能修改。\n");
		if (me->query(to) >= 30 )
			return notify_fail("你的"+gift_desc[to]+"已经大于30点，不能再增加了。\n");
		if ( ((int)me->query(to) + num) > 30)
			return notify_fail("你的"+gift_desc[to]+"增加"+num+"点后将超过30点，不能修改。\n");

		switch (me->query("family/family_name")) {
                        case "桃花岛":
				if (from == "int" && ( me->query("int") <= 24 || ((int)me->query("int") - num) <24 ) )
					return notify_fail("桃花岛弟子悟性要求至少 24。\n");
				break;
			case "天龙寺":
				if (from == "int" && ( me->query("int") <= 18 || ((int)me->query("int") - num) <18 ) )
					return notify_fail("天龙寺弟子悟性要求至少 18。\n");
				break;
			case "大轮寺":
				if (from == "str" && ( me->query("str") <= 20 || ((int)me->query("str") - num) <20) )
					return notify_fail("大轮寺弟子膂力要求至少 20。\n");
				if (from == "con" && ( me->query("con") <= 20 || ((int)me->query("con") - num) <20) )
					return notify_fail("大轮寺弟子根骨要求至少 20。\n");
				break;
		}

		write("请选择 "HIY"Y"NOR"，或任意键取消。\n");
		input_to("confirm_passwd", me, from, to, num);
		return 1;
	}

	if (sscanf(arg, "check %d", num) == 1){

		if ( num > 80 )
			return notify_fail("输入的数值超过了你的隐藏属性合。\n");
		// 计算扣除exp
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		msg = HIG"提示：如果要修改 "+num+" 点属性，你大约要扣除 "+tmpexp+" 点EXP，还剩 "+newexp+" 点EXP。\n"NOR;

		if ( newexp < 95000 )
			msg += HIR"抱歉：修改"+num+"点属性后经验将不够 "+MIN_EXP+" ，建议你一次少修改几点属性。\n"NOR;
		if (me->query_skill("jinshe-zhangfa",1) || me->query_skill("jinshe-jianfa",1))
			msg += HIR"注意：如果修改臂力高于20，金蛇剑法和金蛇掌法将被删除。\n"NOR;
                
                if (me->query_skill("pixie-jian",1))
			msg += HIR"注意：如果修改臂力高于28，辟邪剑法将被删除。\n"NOR;

		if (me->query("zhou/jieyi"))
			msg += HIR"注意：如果修改悟性高于25，左右互搏、空明拳将被删除。\n"NOR;

		if (me->query("dali/meet_dy1") && me->query_skill("lingbo-weibu", 1))
			msg += HIR"注意：如果修改悟性低于22，凌波微步将被删除。\n"NOR;

		write(msg);
		return 1;
	}
	return help();
}

private void confirm_passwd(string yn, object me, string from, string to, int num)
{
	int exp, newexp, tmpexp;

	if ( yn[0]!='y' && yn[0]!='Y' ) {
		write("你取消了给修改先天属性的操作。\n");
		return;
	}
	// 计算扣除exp
	exp = me->query("combat_exp", 1);
	newexp = check_exp(exp,num);
	tmpexp = exp - newexp;

	me->start_busy(1);

	me->add(from, -num);
	me->add(to, num);
	me->add("combat_exp", -tmpexp);

	// 膂力限制金蛇秘籍
	if ( me->query("str") > 20) {
		me->delete_skill("jinshe-zhangfa");
		me->delete_skill("jinshe-jianfa");
	}
	// 膂力限制辟邪剑法
	if ( me->query("str") > 28) {
		me->delete_skill("pixie-jian");
	}
	// 悟性限制读书写字
	if (me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);

	// 双手互搏要求悟性 <= 25
	if (me->query("int") > 25){
		me->delete("double_attack");
		me->delete("zhou/jieyi");
		me->delete("zhou/hubo");
                me->delete_skill("kongming-quan");
	}

	// 凌波微步要求悟性 >= 22
	if ( me->query("int") < 22 ){
		me->delete("dali/meet_dy1");
		me->delete_skill("lingbo-weibu", 1);		
	}

	write("你将"+num+"点"+gift_desc[from]+"调整到"+gift_desc[to]+"上，你被扣除了 "+tmpexp+" 点经验。\n", me);
        me->delete_temp("cgift");
	me->setup();
	me->save();
	log_file("static/ADJUST",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"调整"+num+"点"+gift_desc[from]
		+"到"+gift_desc[to]+"上，扣除 "+tmpexp+" 点经验，剩余"+newexp+"\n",
		me,
		({ me })
	);
	return;
}

int help()
{
	write("本指令用来修改先天属性。\n");
	write("每点属性修改将扣除1% exp。\n");
	write("EXP不足"+MIN_EXP+"不能修改属性。\n");
	write("指令格式：\n");
	write("计算扣除损失：cgift check <要修改的点数>\n");
	write("修改属性：cgift <点数> <要扣除的天赋> to <要增加的天赋>\n");
	write("比如：你要把一点膂力加到悟性上，你可以用："HIG" cgift 1 str to int "NOR"\n");
	write("四项先天属性代号如下:膂力:str,根骨:con,身法:dex,悟性:int\n");
	write("请慎重使用。\n");
	write("\n特别注意：经验值小于1M不能减少悟性。\n");
	return 1;
}
