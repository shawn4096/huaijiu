mapping *wheres=({ 
    (["chinese":                "峨嵋",
       "weizhi" :              "/d/emei/gudelin3",])
           });

int main(object me, string arg)
{
	string num = "12345";

	write(sprintf("%O %O\n", getuid(), geteuid()));
	if (!arg) arg = "";
/*
	tell_room(environment(me),
		sprintf("如果系统支持 MD5，crypt(\"%s\", \"$1$ShuJian\") = %s\n", arg, crypt(arg, "$1$ShuJian")));
	tell_room(environment(me), sprintf("如果系统不支持 MD5，crypt(\"%s\", \"$1$\") = %s\n", arg, crypt(arg, "$1")));
*/
	write(num[<9..<7]+","+num[<6..<4]+","+num[<3..<1]+"\n");
	write(sscanf("aa.old", "%s", num)+num+"\n");
	write(strsrch("12345", "[0m")+"\n");
	write(sscanf("aa", "%sa", num)+num+"\n");
	write(sizeof(wheres)+"\n");
	write(sprintf("%O%O\n", localtime(time()), ctime(time())));
	write(sprintf("%'XY'-10s%'YX'10d", CHINESE_D->chinese_time(0), 0));
	write("\n");
	write(sprintf("%O\n", stat(arg)));
	return 1;
}
