// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;
// pair<int,int> findRange(const vector<int>& nums, int sn) {
//     pair<int,int> range(-1, -1);//初始化范围为-1,表示找不到
//     int n = nums.size();
//     if(n == 0) {
//         return range;
//     }
//     // 判断是否存在循环覆盖
//     bool hasLoop = false;
//     for(int i = 1;i < n;i++) {
//         if(nums[i]< nums[i-1]) {
//             hasLoop = true;
//             break;
//         }
//     }
//     //循环覆盖的情况下,采用两次二分搜索
//     if(hasLoop){
//         int left = 0;
//         int right = n-1;
        
//         //第一次二分搜索找到最小值的位置
//         while(left < right){
// }
// int mid = left +(right-left)/2;if(nums[mid]> nums[right]){
// left = mid + 1;
// }else{
// right = mid;int start = left;left = 0;right = n-1;
// //第二次二分搜索找到目标值的起始位置和結束位置while(left <= right)
// int mid = left +(right-left)/2;int realMid =(mid + start)%n;对于循环覆盖的数组,要根据偏移量重新计算索引if(nums[realMid]== sn){
// range.first = realMid;right = mid-1;
// }else if(nums[realMid]< sn){
// left = mid + 1;
// }else{
// }
// right = mid-1;
// }}
// }
// 如果找到了起始位置,继续搜索结束位置
// if(range.first！=-1){
// left = 0;right = n-1;while(left <= right){
// int mid = left +(right-left)/2;int realMid =(mid + start)%n;//对于循环覆盖的数组,要根据偏移量重新计算索引if(nums[realMid]== sn){
// range.second = realMid;left = mid + 1;
// }else if(nums[realMid]< sn){
// left = mid + 1;
// }else{
// right = mid-1;}}}}

// //普通情况下,采用线性搜索
// else{
// for(int i = θ;i < n;i++){
// if(nums[i]== sn){
// range.first = i;更新起始位置break;for(int i = n-1;i >= θ;i--){
// if(nums[i]== sn){
// range.second = i;//更新結束位置
// break;return range;
// lint main() {
// vector<int> nums = f0, 1, 2, 2, 2, 3, 4}; int sn = 3; int n; cin>>n; int sn; vector<int> nums(n); for(int i=0;i<n;i++){
// cin>>nums[i];
// }
// cin>>sn; pair<int, int> range = findRange(nums, sn); if (range. first != -1 && range. second != -1) {
// cout << range. first << ""<< range. second << endl;
// } else {
// return 0;
// }
// return 0;
// }