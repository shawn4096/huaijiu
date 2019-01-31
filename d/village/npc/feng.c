// feng.c ������

inherit NPC;
inherit F_DEALER;

string ask_ylj4();
string ask_ylj5();

void create()
{
        set_name("������", ({ "feng tiejiang", "feng", "tiejiang" }) );
        set("gender", "����" );
        set("age", 53);
        set("long", 
"���������ǳ��������������������ˣ�˫�۱��̻�޹���ֺ���ϸ��\n"
"���Ȳзϣ������³���һ�����ȡ�\n");
        set("combat_exp", 50000);

        set("str", 24);
        set("dex", 17);
        set("con", 28);
        set("int", 27);
        set("shen_type", 1);

        set("attitude", "friendly");
        set_skill("dodge", 70);
        set_skill("hammer", 40);
        set_skill("parry", 60);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set("vendor_goods", ({
                __DIR__"obj/hammer",
        }));
        set("inquiry", ([
                "name": "С���շ룬�����˶����ҷ�������",
                "here": "������С�˺��ڵ����ӣ�С�˾�ס����ߵ����ӡ�",
                "��ͷ": "��ͷ... ��Ǹ����ͷ�Ѿ�������...",
                "����": "������С������������������ã�һ��ֻҪ������Ǯ��",
                "����": (: ask_ylj4 :),
                "ʦ��": (: ask_ylj5 :),
                "��Ĭ��" : "�������������С���Ѿ��þ�û����������...",
                "���Ŷݼ�" : "�Ƕ���Сʱ��ѧ�ģ�ƽʱû�½���ư��ˡ�",
        ]) );
        setup();
        add_money("coin", 50);
       	carry_object(ARMOR_D("armor/cloth"))->wear();
}


int accept_object(object me, object ob)
{
        object sword;
        if (ob->query("id") =="mowen xuantie") {
            if(me->query_temp("ylj/step4")) {
            	me->delete_temp("ylj/step4");
            	me->set_temp("ylj/step5", 1 );
                say("������˵����������ī���������ô���������Ҫ�õ��һ��������Ĳ���֮�ܣ�δ��ʦ����ɣ�����......\n");
	        return 1;
              	}
	        else say("�ⶫ����Ҫ��û�á�\n");
        }
        else if (ob->query("id") == "ling pai") {
             if(me->query_temp("ylj/stepend") && environment(this_object())->query("short") == "������" ) {
                sword = unew(BINGQI_D("sword/youlong-jian"));
        	if( clonep(sword) ) {
        		sword->move(me);
	        	me->delete_temp("ylj/stepend");
                	say("��Ĭ���ϲ������������Ϊ����ֻ�о��������Ա����......\n");
		        return 1;
                	}
              	}
		else say("�ⶫ����Ҫ��û�á�\n");
        }
return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

string ask_ylj4()
{
        object me;
        me = this_player();
        if ( !me->query_temp("ylj/step3") )
        	return "���ں�������Լ���ȥȡ�ɡ�\n";
        me->delete_temp("ylj/step3");
        command("look "+me->query("id"));
       	me->set_temp("ylj/step4",1);
	return "��λ" + RANK_D->query_respect(me) + "���Ƿ���������Ĳ��ϣ�\n";
}

string ask_ylj5()
{
        object me, obj;
        me = this_player();
        if ( !me->query_temp("ylj/step5") )
        	return "����ʦ������䣬�ɲ���˵�������ġ�\n";
        me->delete_temp("ylj/step5");
	obj = new(__DIR__"obj/ling");
        if( clonep(obj) ) {
        	obj->move(me);
	       	me->set_temp("ylj/step6",1);
		return "�ұ����һ������ӣ�����ʦ���ҩʦ��ʧ�˾����澭��һ\n
ŭ֮�°�����ʦ�ֵܵ��ȽŴ�ϣ������ʦ�ţ��þ�û��ʦ���ˣ���֪ʦ���\n
������Ρ�����ʱ��Ļ����ܷ�Ϊ����һ���һ�����������һ�������ǵ���ʦ\n
���͸��ҵģ�ƾ������ݷ���ʦ����˵Ĭ����ʱ�޿̲������������˼�......\n";
       	}
       	return "����ʦ������䣬�ɲ���˵�������ġ�\n";
}
