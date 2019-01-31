#include <ansi.h>
#define GIFT_CMD        "/cmds/arch/gift"
#define USER_WEAPOND    __DIR__"user_weapond"

int new_gift = 0;

void create()
{
	seteuid(getuid());
	GIFT_CMD->create();
}

int have_new_gift()
{
	if ( new_gift ) return new_gift = 0;
	return new_gift = 1;
}

int query_new_gift() { return new_gift; }

void check_user_weapon(object me);

void get_cloth(object user)
{
	object cloth;
	int i;
	string fam = user->query("family/family_name");

	i = user->query("family/generation");

	switch(fam) {
		case "������":
			if (i <= 35) cloth = new("/d/shaolin/obj/du-cloth");
			if (i == 36) cloth = new("/d/shaolin/obj/xuan-cloth");
			if (i == 37) cloth = new("/d/shaolin/obj/cheng-cloth");
			if (i == 38) cloth = new("/d/shaolin/obj/hui-cloth");
			if (i == 39) cloth = new("/d/shaolin/obj/dao-cloth");
			if (i == 40) cloth = new("/d/shaolin/obj/qing-cloth");
			if (i >= 41) cloth = new("/d/shaolin/obj/cloth");
			if (i < 41 && userp(user))
				switch (user->query("name")[0..1]) {
					case "��":
					case "��":
					case "��":
					case "��":
						user->set("class", "huanxi");
				}
			break;
		case "����":
			if (i <= 35) {
				if(user->query("family/master_name") == "���޼�")
					cloth = new("/d/mingjiao/obj/white-cloth");
				else cloth = new("/d/mingjiao/obj/yel-cloth");
			}
			if (i == 36) cloth = new("/d/mingjiao/obj/red-cloth");
			if (i >= 37) cloth = new("/d/mingjiao/obj/green-cloth");
			break;
		case "������":
			if (user->query("class") == "bonze")
				cloth = new("/d/emei/obj/cloth");
			else    cloth = new("/d/emei/obj/cloth2");
			break;
		case "������":
			if (user->query("tls")) {
				if (i <= 13) cloth = new("/d/tls/obj/jiasha");
				if (i == 14) cloth = new("/d/tls/obj/jiasha1");
				if (i >= 15) cloth = new("/d/tls/obj/jiasha2");
			}
			else {
				if (i <= 14) cloth = new("/d/dali/obj/guanfu1");
				if (i >= 15) cloth = new("/d/dali/obj/guanfu2");
			}
			break;
		case "����Ľ��":
			if(user->query("gender") == "Ů��")
			{
				if (i == 2) cloth = new("/d/mr/obj/cloth6");
				if (i == 3) cloth = new("/d/mr/obj/cloth5");
				if (i == 4) cloth = new("/d/mr/obj/cloth4");
			}
			else
			{
				if (i == 2) cloth = new("/d/mr/obj/cloth3");
				if (i == 3) cloth = new("/d/mr/obj/cloth2");
				if (i == 4) cloth = new("/d/mr/obj/cloth1");
			}
			break;
		case "�䵱��":
			if (i <= 2) cloth = new("/d/wudang/obj/whiterobe");
			if (i >= 3)
				if(user->query("gender") != "Ů��") cloth = new("/d/wudang/obj/greyrobe");
				else cloth = new("/d/wudang/obj/greenrobe");
			break;
		case "������":
			if (i <= 11) cloth = new("/d/xueshan/npc/obj/longxiang-jiasha");
			if (i == 12) cloth = new("/d/xueshan/npc/obj/changsheng-jiasha");
			if (i == 13) cloth = new("/d/xueshan/npc/obj/gongde-jiasha");
			if (i >= 14) cloth = new("/d/xueshan/npc/obj/qinxiu-jiasha");
			break;
		case "��Ĺ��":
			cloth = new("/d/gumu/obj/baiyi");
			break;
		case "��ɽ��":
			if(user->query("gender") == "Ů��"){
				cloth = new(ARMOR_D("cloth"));
				cloth->set("name", HIM "�ۺ�����" NOR);
			}
			else cloth = new(ARMOR_D("changpao1"));
			break;
		default:
			cloth = new(ARMOR_D("cloth"));
			if (fam == "������")
				cloth->set("name", YEL "�Ƹ���" NOR);
			if (fam == "��ɽ��")
				cloth->set("name", BLU "��װ" NOR);
			if (fam == "ؤ��")
				cloth->set("name", HIC "���Ľ���" NOR);
			if (fam == "�һ���")
				cloth->set("name", MAG "�ϳ���" NOR);
			if (fam == "���ư�")
				cloth->set("name", "�̴�װ" );
			if (fam == "������")
				cloth->set("name", "����װ" );
			if (!fam && user->query("class") == "bonze")
				cloth->set("name", "ɮ��");
	}

	if (cloth) {
		cloth->move(user);
		cloth->wear();
	}

	switch(fam)
	{
		case "����Ľ��":
			if(user->query("gender") == "Ů��") cloth = new("/d/mr/obj/xiuhuaxie");
			else cloth = new("/d/mr/obj/guanxue");
			break;
		case "��Ĺ��":
			cloth = new("/d/gumu/obj/buxue1");
			break;
		default:
			cloth = new("/clone/armor/shoes");
			if (user->query("class") == "bonze") cloth->set("name", "ɮЬ");
	}

	if(cloth){
		cloth->move(user);
		cloth->wear();
	}

	// ��������
	if (!present("lingpai", user) && user->query("g_name")) new("/data/group/obj/ling")->move(user);

	// �������
	if (user->query("gender") == "Ů��") {
		if (!present("yu pei", user) && user->query("marry")) new("/clone/misc/marry-token")->move(user);
	} else
		if (!present("xiang nang", user) && user->query("marry")) new("/clone/misc/marry-token")->move(user);

	// class ����
	if (user->query("gender") == "����")
		user->set("class", "eunuch");
	// �Ա����
	switch (user->query("class")) {
		case "eunach":
			user->set("class", "eunuch");
		case "eunuch":
			user->set("gender", "����");
		case "bonze":
		case "huanxi":
		case "lama":
		case "taoist":
			user->delete("marry");
	}

	// ���վ���
	if (user->query("birthday") + user->query("mud_age") > time())
		user->set("birthday", time() - user->query("mud_age"));

	if (mapp(user->query("user_weapon")))
		USER_WEAPOND->check_user_weapon(user);

	if (new_gift && wizardp(user))
		GIFT_CMD->launching(user);
}

int get_object(object ob, object me)
{
	if( ob->is_character()
	|| ob->query("book")
	|| ob->query("imbued")
	|| ob->query("old_ob") == me ) return 0;
	return ob->query("unique");
}

void check_inventory(object me)
{
	int i;
	string desc;
	object *inv;

	if (!objectp(me) || !interactive(me) || !living(me) || wizardp(me) || me->is_fighting()) return;

	if (!new_gift
	|| !userp(me)
	|| me->query("registered") < 2
	|| me->is_ghost()
	|| me->query("mud_age") < 86400
	) ;
	else GIFT_CMD->launching(me);

	if (desc = strip(me->query("long"))) {
		if (strsrch(desc, "\n") > 80) {
			me->delete("long");
			tell_object(me, "�������̫���ˣ������� describe\n");
		} else if (strsrch(desc, "ɱ����") > 5) {
			me->delete("long");
			tell_object(me, "�����������������ᣬ������ describe\n");
		}
	}
	inv = deep_inventory(me);
	if( sizeof(inv) > 35 || me->over_encumbranced()) {
		i = random(sizeof(inv));
		if (inv[i]->query_autoload()) return;
		if (inv[i]->is_character()) return;
		if (inv[i]->query("equipped")) return;
		tell_object(me,
			"��ͻȻ����һ"+inv[i]->query("unit") + inv[i]->name() + "�����ˣ������Ƕ���̫���ˡ�\n"
		);
		destruct(inv[i]);
	}
	inv -= ({ 0 });
	if( environment(me)->query("no_fight") &&
	(me->query("combat_exp") < random(1000000) || me->query_idle( me ) > 120)){
		if(!i = sizeof(inv = filter_array(inv,(:get_object:), me))) return;
		me->add_temp("inv_check", 1);
		if( me->query_temp("inv_check") < 4 ) return;
		if( random(10) < i ){
			i = random(i);
			tell_object(me, "��ͻȻ�������ϵ�һ"+inv[i]->query("unit") + inv[i]->name() + "�����ˣ�\n");
			if((string)inv[i]->query("equipped")) inv[i]->unequip();
			destruct(inv[i]);
			me->delete_temp("inv_check");
		}
	}
}
